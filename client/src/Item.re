let component = ReasonReact.statelessComponent("Item");

module Styles = {
  open Css;
  let item = style([
    border(px(1), `solid, hex("898989")),
    borderRadius(px(4)),
    padding(rem(1.0)),
    marginBottom(rem(0.25))
  ])
};

let make = (~item : Api.item, ~doneAction, _children) => {
  ...component,
  render: _self =>
    <div className=Styles.item>
      <h3>
          {ReasonReact.string(string_of_int(item.id))}
      </h3>
      <button onClick=doneAction>
          {ReasonReact.string("Done")}
      </button>
      <p> {ReasonReact.string(item.text)} </p>
    </div>,
};
