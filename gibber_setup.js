////////////ARDUINO CODE//////////////////
ard = () => {
  data = window.serialvalue;
  state = JSON.parse(data);
  Var1 = 20;
  Var2 = 13;
  switch (state.varSelect) {
    case 0:
      Var1 = state.value;
      break;
    case 1:
      Var2 = state.value;
  }
};
setInterval(ard, 100);
//////////////////////////////////////////
use("hydra").then((__init) => __init());
voronoi(() => Var1, Math.sin(time), 0.8).out(o0);
voronoi(() => Var1, Math.sin(time), 0.8)
  .modulateKaleid(osc(() => Var2, 0.3, 0.5))
  .out(o1);
render();
