let getIcon: string => string = [%raw
  {| function (name) {
      // Still have to handle default case somehow... Ideally
      // pure CSS solution?
      return 'http://media.onetricks.net/' + name.toLowerCase() + 'square-min.png'
}
|}
];
[@react.component]
let make = (~name, ~mini) => {
  let miniCN = if (mini) {"mini-"} else {""};
  let imgCN = miniCN ++ "champ-icon";
  let championIconPath = getIcon(name);
  <img
    className=imgCN
    src=championIconPath
    alt={name ++ " " ++ "One Trick Pony/Ponies"}
  />;
};
