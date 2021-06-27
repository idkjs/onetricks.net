let ste = (str: string) => React.string(str);

let ite = (int: int) => int |> string_of_int |> ste;

let ate = (array: array('a)) => React.array(array);

let lte = (list: list('a)) => list |> Array.of_list |> React.array;

let getEventValue = event => event->ReactEvent.Form.target##value;
