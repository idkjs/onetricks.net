let component = ReasonReact.statelessComponent("Champion");

let make = (~name, ~number, ~handleImageLoad) => {
  ...component,
  render: _self => {
    let len = String.length(string_of_int(number));
    let digitStr =
      (
        if (len == 1) {
          "one";
        } else {
          "two";
        }
      )
      ++ "-digit";
    let numberStyle = "number-text" ++ " " ++ digitStr;
    <div className="champ-square">
      <div className="overlay">
        <span className=numberStyle>
          (ReasonReact.stringToElement(string_of_int(number)))
        </span>
      </div>
      <ChampIcon name mini=false handleImageLoad />
    </div>;
  }
};

let default =
  ReasonReact.wrapReasonForJs(~component, jsProps =>
    make(
      ~name=jsProps##name,
      ~number=jsProps##number,
      ~handleImageLoad=jsProps##handleImageLoad
    )
  );