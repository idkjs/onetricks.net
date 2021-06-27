
[@react.component]
let make = (~champions, ~leagueType: Rank.rank=Rank.All) => {

    <div className="champs">
      (
        ReactUtils.lte(
          List.map(
            (pair: TTypes.oneTrick) =>
              <span
                className="champ-open-links fade-in"
                key=pair.champion
                href="#"
                onClick=(
                  _event =>
                    ReasonReactRouter.push(
                      "/champions/"
                      ++ String.lowercase_ascii(pair.champion)
                      ++ Rank.toRoute(leagueType),
                    )
                )>
                <Champion
                  name=pair.champion
                  number=(List.length(pair.players))
                  key=pair.champion
                />
              </span>,
            champions,
          ),
        )
      )
    </div>
};
