type kind =
  | Item
  | ActualPerk
  | PerkStyle
  | SummonerSpell
  | Role;

[@react.component]
let make = (~kind: kind, ~itemId: int, ~className="") => {
  let imgSrc = (kind, itemId) => {
    "http://s3-us-west-1.amazonaws.com/media.onetricks.net/images/"
    ++ (
      switch (kind) {
      | Item => "items"
      | SummonerSpell => "summoner-spells"
      | ActualPerk => "perks/actual"
      | PerkStyle => "perks/styles"
      | Role => "roles"
      }
    )
    ++ "/"
    ++ string_of_int(itemId)
    ++ ".png";
  };

  <img className src={imgSrc(kind, itemId)}  />;
};
