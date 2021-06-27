
module Styles = {
  open Css;
  let sort =
    style([
      display(`block),
      width(`percent(100.)),
      height(`percent(100.)),
      cursor(`pointer),
      padding2(~v=px(10), ~h=`zero),
      hover([backgroundColor(hex("455A64")), cursor(`pointer)]),
    ]);
  let activeSort = style([backgroundColor(hex("455A64"))]);
};

let grabTriString = (~sortKey, ~activeSortKey, ~isReversed) =>
  if (sortKey === activeSortKey) {
    if (isReversed) {{js|▲|js}} else {{js|▼|js}};
  } else {
    "";
  };
[@react.component]
let make =
    (
      ~onSort: Sort.sort => unit,
      ~sortKey: Sort.sort,
      ~activeSortKey: Sort.sort,
      ~isReversed,
      ~children,
    ) => {
{
    let triString = grabTriString(~sortKey, ~activeSortKey, ~isReversed);
    let triangle =
      if (String.length(triString) > 0) {
        <span className="sort-tri"> (ReactUtils.ste(triString)) </span>;
      } else {
        React.null;
      };
    let cn =
      Styles.sort
      ++ (
        if (sortKey == activeSortKey) {
          " " ++ Styles.activeSort;
        } else {
          "";
        }
      );
    <span className=cn onClick=(_event => onSort(sortKey))>
      (ReactUtils.ste(children))
      (ReactUtils.ste(" "))
      triangle
    </span>;
  }
};
