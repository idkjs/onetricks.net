
let disclaimerEl =
  ReactUtils.ste(
    "This web app isn't endorsed by Riot Games and doesn't reflect the views or opinions of Riot Games or anyone officially involved in producing or managing League of Legends. League of Legends and Riot Games are trademarks or registered trademarks of Riot Games, Inc.\nLeague of Legends \169 Riot Games, Inc. This product is not endorsed, certified\nor otherwise approved in any way by op.gg, and lolking or any of their\naffiliates. All game data is powered by Riot's API. ",
  ); /* notice space */

[@react.component] let make = ()=> {

    <div className="copyright">
      disclaimerEl
      <a
        href="https://github.com/ChauTNguyen/OneTricks"
        rel="noopener noreferrer"
        target="_blank"
        id="src-code">
        (ReactUtils.ste("src code"))
      </a>
    </div>
};
