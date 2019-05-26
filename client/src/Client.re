module IntMap = Map.Make({
  type t = int;
  let compare = compare
});

type state = {
  input: string,
  loading: bool,
  items: IntMap.t(Api.item),
};

type action =
/* UI */
  | UpdateInput(string)
  | Reload
  | AddItem
  | Done(int)
/* Server */
  | FinishedLoading
  | NewItem(Api.item)
  | DeleteItem(int);

let component = ReasonReact.reducerComponent("Client");


let make = _children => {
  ...component,
  initialState: () => {input: "", loading: true, items: IntMap.empty},
  didMount: self => self.send(Reload),
  reducer: (action, state) =>
    switch (action) {
    /* UI */
    | UpdateInput(input) => ReasonReact.Update({...state, input})
    | Reload =>
      ReasonReact.UpdateWithSideEffects({...state, loading: true},
        ( self => {Api.getApiItem()
                   |> Js.Promise.then_(r => {
                       List.map((id) => {
                                Api.getApiItemByItemId(id)
                                |> Js.Promise.then_(item => {
                                    self.send(NewItem(Belt.Result.getExn(item)));
                                    Js.Promise.resolve();
                                  });
                                ();
                                },
                                Belt.Result.getExn(r))
                      self.send(FinishedLoading)
                      Js.Promise.resolve();
                      });
                   ();}))
    | AddItem =>
      ReasonReact.UpdateWithSideEffects({...state, input: ""},
        ( self => {Api.postApiItem(state.input)
                   |> Js.Promise.then_(id => {
                       Api.getApiItemByItemId(Belt.Result.getExn(id))
                       |> Js.Promise.then_(item => {
                           self.send(NewItem(Belt.Result.getExn(item)));
                           Js.Promise.resolve();
                         })
                      Js.log(string_of_int(Belt.Result.getExn(id)));
                      Js.Promise.resolve();
                      });
                   ();}))
    | Done(id) =>
      ReasonReact.SideEffects(self => {
                        Api.deleteApiItemByItemId(id)
                        |> Js.Promise.then_(x => {
                            self.send(DeleteItem(id));
                            Js.Promise.resolve();
                          });
       ();
     })
    /* Server */
    | FinishedLoading =>
      ReasonReact.Update({...state, loading: false})
    | NewItem(item) => 
      ReasonReact.Update({...state, items: IntMap.add(item.id, item, state.items)})
    | DeleteItem(id) => 
      ReasonReact.Update({...state, items: IntMap.remove(id, state.items)})
    },
  render: self =>
    <div>
      <form
        onSubmit={
          ev => {
            ReactEvent.Form.preventDefault(ev);
            self.send(Reload);
          }
        }>
        <label htmlFor="reload"> {ReasonReact.string("Reload")} </label>
        <button type_="submit">
          {ReasonReact.string("Reload")}
        </button>
      </form>
      <form
        onSubmit={
          ev => {
            ReactEvent.Form.preventDefault(ev);
            self.send(AddItem);
          }
        }>
        <input
          id="search"
          name="search"
          value={self.state.input}
          onChange={
            ev => {
              let value = ReactEvent.Form.target(ev)##value;
              self.send(UpdateInput(value));
            }
          }
        />
        <button type_="submit">
          {ReasonReact.string("Add item")}
        </button>
      </form>
      <div>
        {
          self.state.loading ?
            ReasonReact.string("Loading...") :
            IntMap.bindings(self.state.items)
            |> Array.of_list
            |> Array.map(((id, item)) =>
                <Item key={string_of_int(id)}
                      item={item} 
                      doneAction={child => self.send(Done(id))}
/>
               )
            |> ReasonReact.array
        }
      </div>
    </div>,
};
