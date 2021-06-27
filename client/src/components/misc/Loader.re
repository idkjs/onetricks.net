let loaderPath: string = [%raw {|
  require("../assets/misc/loading.svg")
|}];
[@react.component]
let make = () => {
  <div className="loader center-align">
    <img src=loaderPath className="loader-img" alt="Loading!" />
  </div>;
};
