[@react.component]
let make = (~onClick, ~active, ~children) => {
  let cond =
    List.mem(String.lowercase_ascii(children), Array.to_list(active));
  let activeCN: string = if (cond) {" filter-btn-active"} else {""};
  let className: string = "filter-rg-btn" ++ activeCN;
  <button className onClick> {ReactUtils.ste(children)} </button>;
};
