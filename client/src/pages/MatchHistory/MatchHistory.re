open TTypes;

type action =
  | SetMatches(option(miniGameRecords), bool);

type state = {
  matches: option(miniGameRecords),
  /* Note that isLoading does not reset back to false on regions change at the moment. */
  isLoading: bool,
};

module Styles = {
  open Css;
  let table =
    style([
      textAlign(`center),
      tableLayout(`auto),
      media("only screen and (min-width: 768px)", [width(`percent(100.))]),
    ]);
  let icon =
    style([
      width(px(25)),
      height(px(25)),
      marginTop(px(10)),
      media(
        "only screen and (min-width: 768px)",
        [width(px(35)), height(px(35))],
      ),
    ]);
  let blockIcon =
    style([display(`block), margin2(~v=`zero, ~h=`auto), padding(px(5))]);
  let rowWin =
    style([
      background(
        linearGradient(
          `deg(90.),
          [
            (zero, rgba(67, 160, 71, `num(0.6))),
            (pct(90. *. 2.), rgba(38, 50, 56, `num(0.55))),
          ],
        ),
      ),
    ]);
  let rowLose =
    style([
      background(
        linearGradient(
          deg(90.),
          [
            (zero, rgba(229, 57, 53, `num(0.6))),
            (pct(90. *. 2.), rgba(38, 50, 56, `num(0.55))),
          ],
        ),
      ),
    ]);
};
[@react.component]
let make =
    (~championName: string, ~ranks: Rank.ranks, ~regions: Region.regions) => {
  let update = cb =>
    OneTricksService.getChampionIdFromName(championName, championId =>
      switch (championId) {
      | Some(id) =>
        OneTricksService.getMatchHistoryForChampionAndRegions(
          ~ranks=
            switch (ranks) {
            | [Rank.All] => [Rank.Challenger, Rank.Masters]
            | _ => ranks /* singular */
            },
          ~regions,
          ~championId=id,
          ~roles=[
            Role.Top,
            Role.Middle,
            Role.Jungle,
            Role.DuoCarry,
            Role.Support,
          ],
          payload =>
          cb(payload)
        )
      | None => cb(None)
      }
    )
    |> ignore;

  let (state, dispatch) =
    React.useReducer(
      (_state, action) =>
        switch (action) {
        | SetMatches(matches, isLoading) => {matches, isLoading}
        },
      {matches: Some([]), isLoading: true},
    );
  React.useEffect0(() => {
    update(p => dispatch(SetMatches(p, false)));
    Some(
      () => {
        dispatch(SetMatches(state.matches, true));
        update(p => dispatch(SetMatches(p, false)));
      },
      // state;
    );
  });
  switch (state.isLoading, state.matches) {
  | (false, Some([])) =>
    ReactUtils.ste(
      "No games found. Either there are no one tricks playing this champion in this region or set of regions, or the current players probably do not play their one trick champions anymore.",
    )
  | (false, Some(matches)) =>
    <table className=Styles.table>
      <thead>
        <tr>
          <th> {ReactUtils.ste("Region")} </th>
          <th> {ReactUtils.ste("Name")} </th>
          <th> {ReactUtils.ste("KDA")} </th>
          <th />
          <th />
          <th />
          <th />
        </tr>
      </thead>
      <tbody>
        {ReactUtils.lte(
           matches
           |> List.map(el =>
                <tr
                  key={string_of_int(el.gameId)}
                  className={el.didWin ? Styles.rowWin : Styles.rowLose}>
                  <td>
                    {ReactUtils.ste(
                       el.region |> Region.toString |> String.uppercase_ascii,
                     )}
                  </td>
                  <td> {ReactUtils.ste(el.name)} </td>
                  <td>
                    <div>
                      <KDA
                        kda={
                          kills: el.kda.kills,
                          deaths: el.kda.deaths,
                          assists: el.kda.assists,
                        }
                      />
                    </div>
                    <div>
                      <KDA
                        kda={
                          kills: el.kda.kills,
                          deaths: el.kda.deaths,
                          assists: el.kda.assists,
                        }
                        asDecimal=true
                      />
                    </div>
                  </td>
                  <td>
                    <S3Image
                      kind=S3Image.ActualPerk
                      itemId={el.perks.perk0}
                      className={Styles.icon ++ " " ++ Styles.blockIcon}
                    />
                    <S3Image
                      kind=S3Image.PerkStyle
                      itemId={el.perks.perkSubStyle}
                      className={Styles.icon ++ " " ++ Styles.blockIcon}
                    />
                  </td>
                  <td>
                    <S3Image
                      kind=S3Image.SummonerSpell
                      itemId={el.summonerSpells.d}
                      className={Styles.icon ++ " " ++ Styles.blockIcon}
                    />
                    <S3Image
                      kind=S3Image.SummonerSpell
                      itemId={el.summonerSpells.f}
                      className={Styles.icon ++ " " ++ Styles.blockIcon}
                    />
                  </td>
                  <td>
                    {ReactUtils.lte(
                       el.items
                       |> List.mapi((index, item) =>
                            if (item != 0) {
                              <S3Image
                                kind=S3Image.Item
                                itemId=item
                                className=Styles.icon
                                key={
                                  string_of_int(el.gameId)
                                  ++ "-"
                                  ++ string_of_int(item)
                                  ++ "-"
                                  ++ string_of_int(index)
                                }
                              />;
                            } else {
                              React.null;
                            }
                          ),
                     )}
                  </td>
                  <td>
                    <S3Image
                      kind=S3Image.Item
                      itemId={el.trinket}
                      className=Styles.icon
                    />
                  </td>
                </tr>
              ),
         )}
      </tbody>
    </table>
  | (false, None) =>
    ReactUtils.ste(
      "There was an error with the server. Sorry about this! It'll probably be fixed by the next day.",
    )
  | (true, _) =>
    ReactUtils.ste(
      "Currently loading match history! Please wait. This might take a while if the data is uncached.",
    )
  };
};
