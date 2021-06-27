module Router = Router.Router;

module Styles = {
  open Css;
  let link =
    style([
      color(white),
      cursor(`pointer),
      textTransform(uppercase),
      fontWeight(`bold),
      hover([
        color(white),
        cursor(`pointer),
        borderBottom(px(1), `solid, white),
        textTransform(uppercase),
      ]),
    ]);
  let activeLink =
    style([
      color(white),
      borderBottom(px(1), `solid, white),
      fontWeight(`bold),
    ]);
  let className = (isActive: bool) =>
    link
    ++ (
      if (isActive) {
        " " ++ activeLink;
      } else {
        "";
      }
    );
};

[@react.component]
let make = (~route: RouterConfig.route, ~isActive: bool, ~children) => {
  <Router.Link route>
    <span className={Styles.className(isActive)}>
      {children}
    </span>
  </Router.Link>;
};
