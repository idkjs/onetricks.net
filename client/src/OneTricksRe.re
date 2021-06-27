open TTypes;

type action =
  | ResetSearchKey
  | SetRegion(string)
  | SetSearchKey(string)
  | SetSortKey(Sort.sort)
  | SetChampionIconsSortKey(Sorts.oneTricksListSort)
  | SetOneTricks(oneTricks)
  | ToggleMultiRegionFilter
  | ToggleMerge
  | ToggleRegion(string)
  | Nothing;

type championPane = {
  searchKey: string,
  sortBy: Sorts.oneTricksListSort,
  threshholdCountToShow: int,
  oneTricks,
};

type misc = {
  areChampionPanesMerged: bool,
  region: Region.region,
  regions: list(Region.region),
  isMultiRegionFilterOn: bool,
  areImagesLoaded: bool,
};

type playersView = {
  sortKey: Sort.sort,
  shouldSortReverse: bool,
};

type state = {
  championPane,
  misc,
  playersView,
};

// module Router = Router.Router;
module Container = Router.Router.Container;
// open RouterConfig;
[@react.component]
let make = () => {
  let (state, dispatch) =
    React.useReducer(
      (state, action) =>
        switch (action) {
        | Nothing =>
          Js.log("Nothing will happen");
          state;
        | SetRegion(value) => {
            ...state,
            misc: {
              ...state.misc,
              region: Region.fromString(value),
            },
          }
        | SetSearchKey(value) => {
            ...state,
            championPane: {
              ...state.championPane,
              searchKey: value,
            },
          }
        | SetSortKey(sortKey) => {
            ...state,
            playersView: {
              sortKey,
              shouldSortReverse:
                if (sortKey == state.playersView.sortKey) {
                  !state.playersView.shouldSortReverse;
                } else {
                  false;
                },
            },
          }
        | SetChampionIconsSortKey(sortKey) => {
            ...state,
            championPane: {
              ...state.championPane,
              sortBy: sortKey,
            },
          }
        | SetOneTricks(oneTricks) => {
            ...state,
            championPane: {
              ...state.championPane,
              oneTricks,
            },
          }
        | ToggleMultiRegionFilter => {
            ...state,
            misc: {
              ...state.misc,
              regions:
                if (state.misc.isMultiRegionFilterOn) {
                  [];
                } else if (Region.toString(state.misc.region) == "all") {
                  Region.list;
                } else {
                  [state.misc.region];
                },
              isMultiRegionFilterOn: !state.misc.isMultiRegionFilterOn,
            },
          }
        | ToggleMerge => {
            ...state,
            misc: {
              ...state.misc,
              areChampionPanesMerged: !state.misc.areChampionPanesMerged,
            },
          }
        | ToggleRegion(r) =>
          let region = Region.fromString(r);
          let newRegions =
            if (state.misc.regions |> List.mem(region)) {
              state.misc.regions |> List.filter(r => r !== region);
            } else {
              List.append(state.misc.regions, [region]);
            };
          {
            ...state,
            misc: {
              ...state.misc,
              regions: newRegions,
            },
          };
        | _ => state
        },
      {
        championPane: {
          searchKey: "",
          sortBy: Sorts.Number,
          threshholdCountToShow: 0,
          oneTricks: [],
        },
        misc: {
          areChampionPanesMerged: true,
          areImagesLoaded: false,
          isMultiRegionFilterOn: false,
          region: Region.All,
          regions: Region.list,
        },
        playersView: {
          sortKey: Sort.WinRate,
          shouldSortReverse: false,
        },
      },
    );
  React.useEffect0(() => {
    let watcherID =
      ReasonReactRouter.watchUrl(url =>
        GoogleAnalytics.send(
          [%raw {| window.location.pathname |}],
          url.search,
        )
      );
    Some(
      () => {
        ReasonReactRouter.unwatchUrl(watcherID);
        OneTricksService.get(payload => dispatch(SetOneTricks(payload)));
      },
    );
  });
  let isActive: (RouterConfig.route, RouterConfig.route) => bool =
    (currentRoute, route) => currentRoute == route;

  let regionatedOneTricks: oneTricks =
    state.championPane.oneTricks
    |> List.map(({champion, players}) => {
         let newPlayers =
           if (!state.misc.isMultiRegionFilterOn
               && Region.toString(state.misc.region) == "all") {
             /* optimization */
             players;
           } else {
             players
             |> List.filter((player: player) =>
                  state.misc.isMultiRegionFilterOn
                    ? state.misc.regions |> List.mem(player.region)
                    : state.misc.region === player.region
                );
           };
         {champion, players: newPlayers};
       })
    |> (
      switch (state.championPane.sortBy) {
      | Sorts.WinRate => Sorts.oneTricksByWinRate
      | _ => Sorts.numberOfOneTricks
      }
    )
    |> List.filter(({players}) => List.length(players) > 0)
    |> OneTricksHelpers.filterBySearchKey(
         String.lowercase_ascii(
           JsUtils.String.keepOnlyAlphabetical(state.championPane.searchKey),
         ),
       );
  <Container>
    ...{(~currentRoute) =>
      <div className="one-tricks-re">
        <Header
          searchKey={state.championPane.searchKey}
          onSearchKeyChange={event =>
            dispatch(SetSearchKey(ReactUtils.getEventValue(event)))
          }
        />
        <Link
          route=RouterConfig.Home isActive={isActive(currentRoute, RouterConfig.Home)}>
          {ReactUtils.ste("home")}
        </Link>
        {ReactUtils.ste(" | ")}
        <Link
          route=RouterConfig.FAQ isActive={currentRoute == RouterConfig.FAQ}>
          {ReactUtils.ste("faq")}
        </Link>
        {ReactUtils.ste(" | ")}
        <Link
          route=RouterConfig.FeatureRequests
          isActive={currentRoute == RouterConfig.FeatureRequests}>
          {ReactUtils.ste("feature requests & bug reports")}
        </Link>
        {ReactUtils.ste(" | ")}
        <Link
          route=RouterConfig.RiotEndorsement
          isActive={currentRoute == RouterConfig.RiotEndorsement}>
          {ReactUtils.ste("(lack of) Riot Endorsement")}
        </Link>
        <ChampionPaneUtilities
          areChampionPanesMerged={state.misc.areChampionPanesMerged}
          isMultiRegionFilterOn={state.misc.isMultiRegionFilterOn}
          regions={
            state.misc.regions |> Array.of_list |> Array.map(Region.toString)
          }
          toggleMerge={_event => dispatch(ToggleMerge)}
          region={Region.toString(state.misc.region)}
          toggleRegion={regionValue => dispatch(ToggleRegion(regionValue))}
          toggleMultiRegionFilter={_event =>
            dispatch(ToggleMultiRegionFilter)
          }
          setRegionFilter={event =>
            dispatch(SetRegion(ReactUtils.getEventValue(event)))
          }
          setChampionIconsSortKey={value =>
            dispatch(SetChampionIconsSortKey(value))
          }
          sortBy={state.championPane.sortBy}
        />
        {switch (
           ReasonReactRouter.dangerouslyGetInitialUrl().path,
           ReasonReactRouter.dangerouslyGetInitialUrl().search,
         ) {
         | (["champions", championName, ...rest], _search) =>
           let url = ReasonReactRouter.dangerouslyGetInitialUrl();
           let rank =
             switch (url.path, url.search) {
             | (["champions", _championName], "rank=challenger") => Rank.Challenger
             | (["champions", _championName], "rank=masters") => Rank.Masters
             | (["champions", _championName], "") => Rank.All
             | (["champions", _championName, _], "rank=challenger") => Rank.Challenger
             | (["champions", _championName, _], "rank=masters") => Rank.Masters
             | (["champions", _championName, _], "") => Rank.All
             | (_, _) => Rank.All
             };
           <ul className="champions-page-nav">
             <li>
               <Link
                 route={RouterConfig.PlayersView(championName, rank)}
                 isActive={rest |> List.length == 0}>
                 {ReactUtils.ste("players")}
               </Link>
             </li>
             <li>
               <Link
                 route={RouterConfig.RunesSummonersItems(championName, rank)}
                 isActive={
                   url
                   |> RouterConfig.isRouteOrSubroute(
                        ~ofRoute=
                          RouterConfig.RunesSummonersItems(
                            championName,
                            rank,
                          ),
                      )
                 }>
                 {ReactUtils.ste("runes, summoners, & items")}
               </Link>
             </li>
             <li>
               <Link
                 route={RouterConfig.Matchups(championName, rank)}
                 isActive={
                   url
                   |> RouterConfig.isRouteOrSubroute(
                        ~ofRoute=RouterConfig.Matchups(championName, rank),
                      )
                 }>
                 {ReactUtils.ste("champion matchups")}
               </Link>
             </li>
             <li>
               <Link
                 route={RouterConfig.MatchHistory(championName, rank)}
                 isActive={
                   url
                   |> RouterConfig.isRouteOrSubroute(
                        ~ofRoute=
                          RouterConfig.MatchHistory(championName, rank),
                      )
                 }>
                 {ReactUtils.ste("match history")}
               </Link>
             </li>
           </ul>;
         | _ => React.null
         }}
        {switch (currentRoute) {
         | RouterConfig.Home =>
           let regionInfoText =
             Region.toDisplayText(
               ~isMultiRegionFilterOn=state.misc.isMultiRegionFilterOn,
               ~region=state.misc.region,
               ~regions=state.misc.regions,
             );
           <ContentPane
             isMultiRegionFilterOn={state.misc.isMultiRegionFilterOn}
             regions={state.misc.regions}
             allPlayers=regionatedOneTricks
             regionInfoText
             areChampionPanesMerged={state.misc.areChampionPanesMerged}
           />;
         | RouterConfig.PlayersView(currentChampion, rank) =>
           let players =
             regionatedOneTricks
             |> OneTricksHelpers.filterPlayersByRank(_, ~rank)
             |> OneTricksHelpers.extractPlayers(~currentChampion, _);
           if (List.length(players) == 0) {
             <div className="empty-results">
               {ReactUtils.ste(
                  "No players found for the champion: "
                  ++ currentChampion
                  ++ ".",
                )}
             </div>;
           } else {
             <PlayersView
               players
               champ=currentChampion
               show=true
               onSort={sortKey => dispatch(SetSortKey(sortKey))}
               sortKey={state.playersView.sortKey}
               sortReverse={state.playersView.shouldSortReverse}
               ranks=[rank]
               regions={
                         if (state.misc.isMultiRegionFilterOn) {
                           state.misc.regions;
                         } else {
                           [state.misc.region];
                         }
                       }
             />;
           };
         | RouterConfig.Matchups(_currentChampion, _rank) =>
           <div>
             {ReactUtils.ste(
                "Matchups will be implemented in the near future!",
              )}
           </div>
         | RouterConfig.MatchHistory(currentChampion, rank) =>
           <MatchHistory
             championName=currentChampion
             ranks=[rank]
             regions={
                       if (state.misc.isMultiRegionFilterOn) {
                         state.misc.regions;
                       } else {
                         [state.misc.region];
                       }
                     }
           />
         | RouterConfig.RunesSummonersItems(currentChampion, rank) =>
           <RunesSummonersItems
             championName=currentChampion
             ranks=[rank]
             regions={
                       if (state.misc.isMultiRegionFilterOn) {
                         state.misc.regions;
                       } else {
                         [state.misc.region];
                       }
                     }
           />
         | RouterConfig.FeatureRequests => <FeatureRequests />
         | RouterConfig.FAQ => <FAQ />
         | RouterConfig.RiotEndorsement => <Copyright />
         | RouterConfig.NotFound => <NotFound />
         }}
      </div>
    }
  </Container>;
};
