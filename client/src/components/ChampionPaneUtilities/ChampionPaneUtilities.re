[@react.component]
let make =
    (
      ~areChampionPanesMerged,
      ~isMultiRegionFilterOn,
      ~regions,
      ~toggleMerge,
      ~toggleRegion,
      ~toggleMultiRegionFilter,
      ~region,
      ~setRegionFilter,
      ~setChampionIconsSortKey,
      ~sortBy,
    ) => {
  let comp =
    <div className="champs-pane-utility">
      <div className="merged-input">
        <div className="float-left">
          <RegionSelectMenu isMultiRegionFilterOn region setRegionFilter />
          <MultiRegionFilter
            isMultiRegionFilterOn
            regions
            toggleMultiRegionFilter
            toggleRegion
          />
        </div>
        <div className="float-right">
          <MergeSeparateBtn areChampionPanesMerged onClick=toggleMerge />
          {switch (
             ReasonReactRouter.dangerouslyGetInitialUrl().path,
             ReasonReactRouter.dangerouslyGetInitialUrl().search,
           ) {
           | ([], "") =>
             <select
               className="sort-select"
               id="sort-select"
               onChange={event => {
                 let value = ReactUtils.getEventValue(event);
                 setChampionIconsSortKey(
                   switch (value) {
                   | "players" => Sorts.Number
                   | "winrate" => Sorts.WinRate
                   | _ => Sorts.Number
                   },
                 );
               }}
               value={
                 switch (sortBy) {
                 | Sorts.Number => "players"
                 | Sorts.WinRate => "winrate"
                 }
               }>
               <option value="players">
                 {ReactUtils.ste("Sort champion icons by number of players")}
               </option>
               <option value="winrate">
                 {ReactUtils.ste("Sort champion icons by win rate")}
               </option>
             </select>
           | _ => React.null
           }}
        </div>
      </div>
    </div>;
  switch (
    ReasonReactRouter.dangerouslyGetInitialUrl().path,
    ReasonReactRouter.dangerouslyGetInitialUrl().search,
  ) {
  | ([], _rest) => comp
  | (["champions", ..._rest], _) => comp
  | _ => React.null
  };
};
