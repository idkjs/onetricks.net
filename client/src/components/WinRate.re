let getHexColorFromWinrate = (wr: float) =>
  (
    if (wr < 50.0) {
      ColorTier.Poor;
    } else if (wr < 55.0) {
      ColorTier.Okay;
    } else if (wr < 60.0) {
      ColorTier.Average;
    } else if (wr < 65.0) {
      ColorTier.Great;
    } else {
      ColorTier.Excellent;
    }
  )
  |> ColorTier.toHex;

[@react.component]
let make = (~wins: int, ~losses: int) => {
  let winsAsFloat = Pervasives.float_of_int(wins);
  let lossesAsFloat = Pervasives.float_of_int(losses);
  let winRate = winsAsFloat /. (winsAsFloat +. lossesAsFloat) *. 100.0;
  let style =
    ReactDOMRe.Style.make(~color=getHexColorFromWinrate(winRate), ());
  <span style>
    {ReactUtils.ste((winRate |> ceil |> int_of_float |> string_of_int) ++ "%")}
  </span>;
};
