
module Styles = {
  /*
   Open the Css module, so we can access the style properties below without prefixing them with Css.
   You can use either Css or CssJs: Css module is using lists, CssJs is using arrays.
   If you're targeting js and/or using Rescript, prefer CssJs
   */
  open Css;

  let table =
    style([
      backgroundColor(hex("37474F")),
      textAlign(`center),
      media("only screen and (min-width: 480px)", [width(`percent(100.))]),
    ]);

  let th = style([borderBottom(px(1), `solid, black)]);
  let rowNumber = style([fontSize(rem(0.8))]);

};
let sortButtonsInfo = [
  (Sort.None, ""),
  (Sort.Region, "region"),
  (Sort.Rank, "rank"),
  (Sort.Name, "name"),
  (Sort.Wins, "wins"),
  (Sort.Losses, "losses"),
  (Sort.WinRate, "win %"),
];

[@react.component]
let make = (~onSort, ~sortKey, ~sortReverse, ~renderableList) => {
  <table className=Styles.table>
    <thead>
      <tr>
        {ReactUtils.lte(
           List.map(
             ((key, displayText)) =>
               <th className=Styles.th>
                 <PlayersSortBtn
                   onSort
                   sortKey=key
                   activeSortKey=sortKey
                   isReversed=sortReverse>
                   ...displayText
                 </PlayersSortBtn>
               </th>,
             sortButtonsInfo,
           ),
         )}
        <th className=Styles.th> {ReactUtils.ste("op.gg")} </th>
      </tr>
    </thead>
    <tbody> {ReactUtils.lte(renderableList)} </tbody>
  </table>;
};
