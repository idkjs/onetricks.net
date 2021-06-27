[@react.component]
let make =
    (
      ~isMultiRegionFilterOn: bool,
      ~regions,
      ~allPlayers,
      ~regionInfoText: string,
      ~areChampionPanesMerged,

    ) => {
  let createHeaderText = (list: list('a), text: string) =>
    string_of_int(List.length(list)) ++ " " ++ text ++ " " ++ regionInfoText;
  {
   
      <div>
        (
          if (isMultiRegionFilterOn && List.length(regions) == 0) {
            <div className="empty-results">
              (ReactUtils.ste("No region is selected."))
            </div>;
          } else {
            React.null;
          }
        )
        (
          if (areChampionPanesMerged) {
            if (List.length(allPlayers) > 0) {
              <div className="content-pane merged-pane">
                <div className="rank-pane">
                  <h5 className="rank-header">
                    (
                      ReactUtils.ste(
                        createHeaderText(
                          allPlayers,
                          "Challenger, Grandmasters, & Masters One Tricks in",
                        ),
                      )
                    )
                  </h5>
                  <ChampionPane champions=allPlayers />
                </div>
              </div>;
            } else {
              React.null;
            };
          } else {
            /* How to utilize partition instead of multiple O(n) filters? */
            let challengers =
              OneTricksHelpers.filterPlayersByRank(
                allPlayers,
                ~rank=Rank.Challenger,
              );
            let grandmasters =
              OneTricksHelpers.filterPlayersByRank(
                allPlayers,
                ~rank=Rank.Grandmasters,
              );
            let masters =
              OneTricksHelpers.filterPlayersByRank(
                allPlayers,
                ~rank=Rank.Masters,
              );
            if (List.length(challengers) === 0
                && List.length(grandmasters) === 0
                && List.length(masters) === 0) {
              React.null;
            } else {
              <div className="content-pane separated-pane">
                (
                  if (List.length(challengers) > 0) {
                    <div className="rank-pane challengers-pane">
                      <h5 className="rank-header">
                        (
                          ReactUtils.ste(
                            createHeaderText(
                              challengers,
                              "Challenger One Tricks in",
                            ),
                          )
                        )
                      </h5>
                      <ChampionPane
                        champions=challengers
                        leagueType=Rank.Challenger
                      />
                    </div>;
                  } else {
                    React.null;
                  }
                )
                (
                  if (List.length(grandmasters) > 0) {
                    <div className="rank-pane grandmasters-pane">
                      <h5 className="rank-header">
                        (
                          ReactUtils.ste(
                            createHeaderText(
                              grandmasters,
                              "Grandmasters One Trick Ponies in",
                            ),
                          )
                        )
                      </h5>
                      <ChampionPane
                        champions=grandmasters
                        leagueType=Rank.Grandmasters
                      />
                    </div>;
                  } else {
                    React.null;
                  }
                )
                (
                  if (List.length(masters) > 0) {
                    <div className="rank-pane masters-pane">
                      <h5 className="rank-header">
                        (
                          ReactUtils.ste(
                            createHeaderText(
                              masters,
                              "Masters One Trick Ponies in",
                            ),
                          )
                        )
                      </h5>
                      <ChampionPane
                        champions=masters
                        leagueType=Rank.Masters
                      />
                    </div>;
                  } else {
                    React.null;
                  }
                )
              </div>;
            };
          }
        )
      </div>
  };
};
