
[@react.component]
let make = (~areChampionPanesMerged, ~onClick) => {

    switch (
      ReasonReactRouter.dangerouslyGetInitialUrl().path,
      ReasonReactRouter.dangerouslyGetInitialUrl().search,
    ) {
    | ([], "") =>
      <button className="merge-sep-button" onClick>
        <span className="merge-sep-text">
          <span className="merge-sep-action">
            (
              ReactUtils.ste(
                if (areChampionPanesMerged) {
                  "Separate into Challenger's, Grandmaster's, & Master's sections"
                } else {
                  "Merge Challenger's, Grandmaster's, & Master's sections"
                },
              )
            )
          </span>
        </span>
      </button>
    | _ => React.null
    }
};
