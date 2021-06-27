[@react.component]
let make =
    (
      ~isMultiRegionFilterOn,
      ~regions,
      ~toggleMultiRegionFilter: unit => unit,
      ~toggleRegion: string => unit,
    ) => {
  <div className="multiple-filter">
    {if (isMultiRegionFilterOn) {
       <FilterRegion toggleRegion toggleMultiRegionFilter regions />;
     } else {
       <div
         className="adv-filtering-open"
         onClick={_event => toggleMultiRegionFilter()}>
         {ReactUtils.ste("Multiple Regions")}
       </div>;
     }}
  </div>;
};
