// Generated by BUCKLESCRIPT VERSION 2.1.0, PLEASE EDIT WITH CARE
'use strict';

var QA          = require("./QA.js");
var List        = require("bs-platform/lib/js/list.js");
var $$Array     = require("bs-platform/lib/js/array.js");
var React       = require("react");
var ReasonReact = require("reason-react/src/ReasonReact.js");

var component = ReasonReact.statelessComponent("FAQ");

var qas = /* :: */[
  /* tuple */[
    "Where to contact for bug reports, feature requests, etc. I appreciate all tips and advice regarding any aspect of this site as well.",
    "lolonetricks@gmail.com"
  ],
  /* :: */[
    /* tuple */[
      "Why isn't this 100% accurate? So and so isn't on here! So and so is on here, but was kicked out! This person isn't masters, this person isn't challenger, etcetc.",
      "It'd be tough to make it perfectly accurate. I simply wanted to give everyone an accurate enough representation of the current one tricks in challengers and masters. Someone should be able to go on the site and get a good enough idea of what champions are being one tricked into the highest level of play.\nI'm still a student in college, and I'm still new to making complete projects. I simply went with the easiest route (when analyzing the data) and deployed ASAP.\nOver the next few weeks, I'll improve it so that we get more up-to-date data though!"
    ],
    /* :: */[
      /* tuple */[
        "This person isn't a 1 trick!",
        "Over the next few weeks, I'll be making drastic changes to the backend as I have more time. I'm working with a few other people to create a more robust algorithm. Although there are slight twists to the phrase one trick pony today, I define it as someone who really excels on one champ, but does below average on other champs. These types of one tricks are much more prominent in higher elo, and I found that a majority of them are easily identifiable and thus are on this list."
      ],
      /* :: */[
        /* tuple */[
          "The na.op.gg link doesn't work.",
          "They changed their name. Try the lolking link instead (lolking will redirect you to their new name). The database will correct the names some time overnight."
        ],
        /* :: */[
          /* tuple */[
            "What you'd make this with?",
            "At a high level: HTML, CSS, JS, React, Express, and MongoDB. Also integrating ReasonML with it now for easy types."
          ],
          /* :: */[
            /* tuple */[
              "Any special mentions?",
              "I'd like to thank Richelle for all the support she has provided me, and Richelle if you're reading this, I hope you stop being a hardstuck D5* player. I'd like to thank all the people who checked out my site in its early stages and provided feedback and encouragement."
            ],
            /* [] */0
          ]
        ]
      ]
    ]
  ]
];

function make() {
  var newrecord = component.slice();
  newrecord[/* render */9] = (function () {
      return React.createElement("div", {
                  className: "faq"
                }, React.createElement("h3", {
                      className: "faq-header"
                    }, "faq"), React.createElement("div", {
                      className: "qa"
                    }, $$Array.of_list(List.map((function (param) {
                                var question = param[0];
                                return ReasonReact.element(/* Some */[question], /* None */0, QA.make(question, param[1], /* array */[]));
                              }), qas))));
    });
  return newrecord;
}

var $$default = ReasonReact.wrapReasonForJs(component, (function () {
        return make(/* () */0);
      }));

exports.component = component;
exports.qas       = qas;
exports.make      = make;
exports.$$default = $$default;
exports.default   = $$default;
exports.__esModule= true;
/* component Not a pure module */
