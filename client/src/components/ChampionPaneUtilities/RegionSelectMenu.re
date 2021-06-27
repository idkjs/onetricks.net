[@react.component]
let make = (~isMultiRegionFilterOn, ~region, ~setRegionFilter) =>
  if (isMultiRegionFilterOn) {
    React.null;
  } else {
    <select
      className="region-select"
      id="region"
      onChange=setRegionFilter
      value=region>
      <option value="all"> {ReactUtils.ste("All Regions")} </option>
      {ReactUtils.ate(
         Array.map(
           region =>
             <option value=region key=region>
               {ReactUtils.ste(String.uppercase_ascii(region))}
             </option>,
           Region.list |> Region.toStringList |> Array.of_list,
         ),
       )}
    </select>;
  };
