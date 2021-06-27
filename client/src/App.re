module Styles = {
  open Css;
  let container = style([maxWidth(px(1024)), margin2(~v=`zero, ~h=`auto)]);
};

[@react.component]
let make = () => {
  <div className=Styles.container> <OneTricksRe /> </div>;
};
