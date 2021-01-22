struct Page {
  const char* const filename;
  const char* const content;
};

constexpr auto web_server_page_content_0 = R"WEB_SERVER(// [snowpack] add styles to the page (skip if no document exists)
if (typeof document !== 'undefined') {
  const code = "* {\n  margin: 0;\n  padding: 0;\n  box-sizing: border-box;\n}\n\n:root {\n  font-family: Helvetica, sans-serif;\n}\n\nbody {\n  margin: 1rem;\n  text-align: center;\n}\n\n.ctrl {\n  margin: 1em;\n}\n\n.ctrl-input {\n  width: 100%;\n  margin: .5rem;\n}\n\n.ctrl-color {\n  width: 10%;\n  margin: .5rem;\n}\n";

  const styleEl = document.createElement("style");
  const codeEl = document.createTextNode(code);
  styleEl.type = 'text/css';
  styleEl.appendChild(codeEl);
  document.head.appendChild(styleEl);
})WEB_SERVER";
constexpr auto web_server_page_content_1 = R"WEB_SERVER((window.webpackJsonp=window.webpackJsonp||[]).push([[0],[function(t,e,n){(function(e){var n=function(t){return t&&t.Math==Math&&t};t.exports=n("object"==typeof globalThis&&globalThis)||n("object"==typeof window&&window)||n("object"==typeof self&&self)||n("object"==typeof e&&e)||function(){return this}()||Function("return this")()}).call(this,n(37))},function(t,e){var n={}.hasOwnProperty;t.exports=function(t,e){return n.call(t,e)}},function(t,e,n){var r=n(5),o=n(6),i=n(13);t.exports=r?function(t,e,n){return o.f(t,e,i(1,n))}:function(t,e,n){return t[e]=n,t}},function(t,e){t.exports=function(t){try{return!!t()}catch(t){return!0}}},function(t,e,n){var r=n(0),o=n(19),i=n(1),u=n(23),c=n(24),a=n(43),f=o("wks"),s=r.Symbol,l=a?s:s&&s.withoutSetter||u;t.exports=function(t){return i(f,t)||(c&&i(s,t)?f[t]=s[t]:f[t]=l("Symbol."+t)),f[t]}},function(t,e,n){var r=n(3);t.exports=!r((function(){return 7!=Object.defineProperty({},1,{get:function(){return 7}})[1]}))},function(t,e,n){var r=n(5),o=n(20),i=n(8),u=n(22),c=Object.defineProperty;e.f=r?c:function(t,e,n){if(i(t),e=u(e,!0),i(n),o)try{return c(t,e,n)}catch(t){}if("get"in n||"set"in n)throw TypeError("Accessors not supported");return"value"in n&&(t[e]=n.value),t}},function(t,e){t.exports=function(t){return"object"==typeof t?null!==t:"function"==typeof t}},function(t,e,n){var r=n(7);t.exports=function(t){if(!r(t))throw TypeError(String(t)+" is not an object");return t}},function(t,e,n){var r=n(40),o=n(18);t.exports=function(t){return r(o(t))}},function(t,e){t.exports=!1},function(t,e,n){var r=n(0),o=n(12),i="__core-js_shared__",u=r[i]||o(i,{});t.exports=u},function(t,e,n){var r=n(0),o=n(2);t.exports=function(t,e){try{o(r,t,e)}catch(n){r[t]=e}return e}},function(t,e){t.exports=function(t,e){return{enumerable:!(1&t),configurable:!(2&t),writable:!(4&t),value:e}}},function(t,e){t.exports={}},function(t,e){t.exports=["constructor","hasOwnProperty","isPrototypeOf","propertyIsEnumerable","toLocaleString","toString","valueOf"]},function(t,e,n){var r=n(19),o=n(23),i=r("keys");t.exports=function(t){return i[t]||(i[t]=o(t))}},function(t,e){t.exports={}},function(t,e){t.exports=function(t){if(null==t)throw TypeError("Can't call method on "+t);return t}},function(t,e,n){var r=n(10),o=n(11);(t.exports=function(t,e){return o[t]||(o[t]=void 0!==e?e:{})})("versions",[]).push({version:"3.8.2",mode:r?"pure":"global",copyright:"© 2021 Denis Pushkarev (zloirock.ru)"})},function(t,e,n){var r=n(5),o=n(3),i=n(21);t.exports=!r&&!o((function(){return 7!=Object.defineProperty(i("div"),"a",{get:function(){return 7}}).a}))},function(t,e,n){var r=n(0),o=n(7),i=r.document,u=o(i)&&o(i.createElement);t.exports=function(t){return u?i.createElement(t):{}}},function(t,e,n){var r=n(7);t.exports=function(t,e){if(!r(t))return t;var n,o;if(e&&"function"==typeof(n=t.toString)&&!r(o=n.call(t)))return o;if("function"==typeof(n=t.valueOf)&&!r(o=n.call(t)))return o;if(!e&&"function"==typeof(n=t.toString)&&!r(o=n.call(t)))return o;throw TypeError("Can't convert object to primitive value")}},function(t,e){var n=0,r=Math.random();t.exports=function(t){return"Symbol("+String(void 0===t?"":t)+")_"+(++n+r).toString(36)}},function(t,e,n){var r=n(3);t.exports=!!Object.getOwnPropertySymbols&&!r((function(){return!String(Symbol())}))},function(t,e,n){var r,o=n(8),i=n(44),u=n(15),c=n(14),a=n(49),f=n(21),s=n(16),l=s("IE_PROTO"),p=function(){},v=function(t){return"<script>"+t+"</"+"script>"},d=function(){try{r=document.domain&&new ActiveXObject("htmlfile")}catch(t){}var t,e;d=r?function(t){t.write(v("")),t.close();var e=t.parentWindow.Object;return t=null,e}(r):((e=f("iframe")).style.display="none",a.appendChild(e),e.src=String("javascript:"),(t=e.contentWindow.document).open(),t.write(v("document.F=Object")),t.close(),t.F);for(var n=u.length;n--;)delete d.prototype[u[n]];return d()};c[l]=!0,t.exports=Object.create||function(t,e){var n;return null!==t?(p.prototype=o(t),n=new p,p.prototype=null,n[l]=t):n=d(),void 0===e?n:i(n,e)}},function(t,e,n){var r=n(1),o=n(9),i=n(46).indexOf,u=n(14);t.exports=function(t,e){var n,c=o(t),a=0,f=[];for(n in c)!r(u,n)&&r(c,n)&&f.push(n);for(;e.length>a;)r(c,n=e[a++])&&(~i(f,n)||f.push(n));return f}},function(t,e){var n=Math.ceil,r=Math.floor;t.exports=function(t){return isNaN(t=+t)?0:(t>0?r:n)(t)}},function(t,e,n){var r=n(50),o=n(0),i=function(t){return"function"==typeof t?t:void 0};t.exports=function(t,e){return arguments.length<2?i(r[t])||i(o[t]):r[t]&&r[t][e]||o[t]&&o[t][e]}},function(t,e,n){var r,o,i,u=n(51),c=n(0),a=n(7),f=n(2),s=n(1),l=n(11),p=n(16),v=n(14),d=c.WeakMap;if(u){var y=l.state||(l.state=new d),g=y.get,b=y.has,h=y.set;r=function(t,e){return e.facade=t,h.call(y,t,e),e},o=function(t){return g.call(y,t)||{}},i=function(t){return b.call(y,t)}}else{var m=p("state");v[m]=!0,r=function(t,e){return e.facade=t,f(t,m,e),e},o=function(t){return s(t,m)?t[m]:{}},i=function(t){return s(t,m)}}t.exports={set:r,get:o,has:i,enforce:function(t){return i(t)?o(t):r(t,{})},getterFor:function(t){return function(e){var n;if(!a(e)||(n=o(e)).type!==t)throw TypeError("Incompatible receiver, "+t+" required");return n}}}},function(t,e,n){var r=n(11),o=Function.toString;"function"!=typeof r.inspectSource&&(r.inspectSource=function(t){return o.call(t)}),t.exports=r.inspectSource},function(t,e,n){var r=n(5),o=n(54),i=n(13),u=n(9),c=n(22),a=n(1),f=n(20),s=Object.getOwnPropertyDescriptor;e.f=r?s:function(t,e){if(t=u(t),e=c(e,!0),f)try{return s(t,e)}catch(t){}if(a(t,e))return i(!o.f.call(t,e),t[e])}},function(t,e,n){var r=n(0),o=n(2),i=n(1),u=n(12),c=n(30),a=n(29),f=a.get,s=a.enforce,l=String(String).split("String");(t.exports=function(t,e,n,c){var a,f=!!c&&!!c.unsafe,p=!!c&&!!c.enumerable,v=!!c&&!!c.noTargetGet;"function"==typeof n&&("string"!=typeof e||i(n,"name")||o(n,"name",e),(a=s(n)).source||(a.source=l.join("string"==typeof e?e:""))),t!==r?(f?!v&&t[e]&&(p=!0):delete t[e],p?t[e]=n:o(t,e,n)):p?t[e]=n:u(e,n)})(Function.prototype,"toString",(function(){return"function"==typeof this&&f(this).source||c(this)}))},function(t,e,n){"use strict";var r,o,i,u=n(34),c=n(2),a=n(1),f=n(4),s=n(10),l=f("iterator"),p=!1;[].keys&&("next"in(i=[].keys())?(o=u(u(i)))!==Object.prototype&&(r=o):p=!0),null==r&&(r={}),s||a(r,l)||c(r,l,(function(){return this})),t.exports={IteratorPrototype:r,BUGGY_SAFARI_ITERATORS:p}},function(t,e,n){var r=n(1),o=n(61),i=n(16),u=n(62),c=i("IE_PROTO"),a=Object.prototype;t.exports=u?Object.getPrototypeOf:function(t){return t=o(t),r(t,c)?t[c]:"function"==typeof t.constructor&&t instanceof t.constructor?t.constructor.prototype:t instanceof Object?a:null}},function(t,e,n){var r=n(6).f,o=n(1),i=n(4)("toStringTag");t.exports=function(t,e,n){t&&!o(t=n?t:t.prototype,i)&&r(t,i,{configurable:!0,value:e})}},function(t,e,n){var r=n(0),o=n(38),i=n(39),u=n(2),c=n(4),a=c("iterator"),f=c("toStringTag"),s=i.values;for(var l in o){var p=r[l],v=p&&p.prototype;if(v){if(v[a]!==s)try{u(v,a,s)}catch(t){v[a]=s}if(v[f]||u(v,f,l),o[l])for(var d in i)if(v[d]!==i[d])try{u(v,d,i[d])}catch(t){v[d]=i[d]}}}},function(t,e){var n;n=function(){return this}();try{n=n||new Function("return this")()}catch(t){"object"==typeof window&&(n=window)}t.exports=n},function(t,e){t.exports={CSSRuleList:0,CSSStyleDeclaration:0,CSSValueList:0,ClientRectList:0,DOMRectList:0,DOMStringList:0,DOMTokenList:1,DataTransferItemList:0,FileList:0,HTMLAllCollection:0,HTMLCollection:0,HTMLFormElement:0,HTMLSelectElement:0,MediaList:0,MimeTypeArray:0,NamedNodeMap:0,NodeList:1,PaintRequestList:0,Plugin:0,PluginArray:0,SVGLengthList:0,SVGNumberList:0,SVGPathSegList:0,SVGPointList:0,SVGStringList:0,SVGTransformList:0,SourceBufferList:0,StyleSheetList:0,TextTrackCueList:0,TextTrackList:0,TouchList:0}},function(t,e,n){"use strict";var r=n(9),o=n(42),i=n(17),u=n(29),c=n(52),a="Array Iterator",f=u.set,s=u.getterFor(a);t.exports=c(Array,"Array",(function(t,e){f(this,{type:a,target:r(t),index:0,kind:e})}),(function(){var t=s(this),e=t.target,n=t.kind,r=t.index++;return!e||r>=e.length?(t.target=void 0,{value:void 0,done:!0}):"keys"==n?{value:r,done:!1}:"values"==n?{value:e[r],done:!1}:{value:[r,e[r]],done:!1}}),"values"),i.Arguments=i.Array,o("keys"),o("values"),o("entries")},function(t,e,n){var r=n(3),o=n(41),i="".split;t.exports=r((function(){return!Object("z").propertyIsEnumerable(0)}))?function(t){return"String"==o(t)?i.call(t,""):Object(t)}:Object},function(t,e){var n={}.toString;t.exports=function(t){return n.call(t).slice(8,-1)}},function(t,e,n){var r=n(4),o=n(25),i=n(6),u=r("unscopables"),c=Array.prototype;null==c[u]&&i.f(c,u,{configurable:!0,value:o(null)}),t.exports=function(t){c[u][t]=!0}},function(t,e,n){var r=n(24);t.exports=r&&!Symbol.sham&&"symbol"==typeof Symbol.iterator},function(t,e,n){var r=n(5),o=n(6),i=n(8),u=n(45);t.exports=r?Object.defineProperties:function(t,e){i(t);for(var n,r=u(e),c=r.length,a=0;c>a;)o.f(t,n=r[a++],e[n]);return t}},function(t,e,n){var r=n(26),o=n(15);t.exports=Object.keys||function(t){return r(t,o)}},function(t,e,n){var r=n(9),o=n(47),i=n(48),u=function(t){return function(e,n,u){var c,a=r(e),f=o(a.length),s=i(u,f);if(t&&n!=n){for(;f>s;)if((c=a[s++])!=c)return!0}else for(;f>s;s++)if((t||s in a)&&a[s]===n)return t||s||0;return!t&&-1}};t.exports={includes:u(!0),indexOf:u(!1)}},function(t,e,n){var r=n(27),o=Math.min;t.exports=function(t){return t>0?o(r(t),9007199254740991):0}},function(t,e,n){var r=n(27),o=Math.max,i=Math.min;t.exports=function(t,e){var n=r(t);return n<0?o(n+e,0):i(n,e)}},function(t,e,n){var r=n(28);t.exports=r("document","documentElement")},function(t,e,n){var r=n(0);t.exports=r},function(t,e,n){var r=n(0),o=n(30),i=r.WeakMap;t.exports="function"==typeof i&&/native code/.test(o(i))},function(t,e,n){"use strict";var r=n(53),o=n(60),i=n(34),u=n(63),c=n(35),a=n(2),f=n(32),s=n(4),l=n(10),p=n(17),v=n(33),d=v.IteratorPrototype,y=v.BUGGY_SAFARI_ITERATORS,g=s("iterator"),b="keys",h="values",m="entries",x=function(){return this};t.exports=function(t,e,n,s,v,S,O){o(n,e,s);var w,L,j,T=function(t){if(t===v&&_)return _;if(!y&&t in P)return P[t];switch(t){case b:case h:case m:return function(){return new n(this,t)}}return function(){return new n(this)}},E=e+" Iterator",I=!1,P=t.prototype,M=P[g]||P["@@iterator"]||v&&P[v],_=!y&&M||T(v),k="Array"==e&&P.entries||M;if(k&&(w=i(k.call(new t)),d!==Object.prototype&&w.next&&(l||i(w)===d||(u?u(w,d):"function"!=typeof w[g]&&a(w,g,x)),c(w,E,!0,!0),l&&(p[E]=x))),v==h&&M&&M.name!==h&&(I=!0,_=function(){return M.call(this)}),l&&!O||P[g]===_||a(P,g,_),p[e]=_,v)if(L={values:T(h),keys:S?_:T(b),entries:T(m)},O)for(j in L)(y||I||!(j in P))&&f(P,j,L[j]);else r({target:e,proto:!0,forced:y||I},L);return L}},function(t,e,n){var r=n(0),o=n(31).f,i=n(2),u=n(32),c=n(12),a=n(55),f=n(59);t.exports=function(t,e){var n,s,l,p,v,d=t.target,y=t.global,g=t.stat;if(n=y?r:g?r[d]||c(d,{}):(r[d]||{}).prototype)for(s in e){if(p=e[s],l=t.noTargetGet?(v=o(n,s))&&v.value:n[s],!f(y?s:d+(g?".":"#")+s,t.forced)&&void 0!==l){if(typeof p==typeof l)continue;a(p,l)}(t.sham||l&&l.sham)&&i(p,"sham",!0),u(n,s,p,t)}}},function(t,e,n){"use strict";var r={}.propertyIsEnumerable,o=Object.getOwnPropertyDescriptor,i=o&&!r.call({1:2},1);e.f=i?function(t){var e=o(this,t);return!!e&&e.enumerable}:r},function(t,e,n){var r=n(1),o=n(56),i=n(31),u=n(6);t.exports=function(t,e){for(var n=o(e),c=u.f,a=i.f,f=0;f<n.length;f++){var s=n[f];r(t,s)||c(t,s,a(e,s))}}},function(t,e,n){var r=n(28),o=n(57),i=n(58),u=n(8);t.exports=r("Reflect","ownKeys")||function(t){var e=o.f(u(t)),n=i.f;return n?e.concat(n(t)):e}},function(t,e,n){var r=n(26),o=n(15).concat("length","prototype");e.f=Object.getOwnPropertyNames||function(t){return r(t,o)}},function(t,e){e.f=Object.getOwnPropertySymbols},function(t,e,n){var r=n(3),o=/#|\.prototype\./,i=function(t,e){var n=c[u(t)];return n==f||n!=a&&("function"==typeof e?r(e):!!e)},u=i.normalize=function(t){return String(t).replace(o,".").toLowerCase()},c=i.data={},a=i.NATIVE="N",f=i.POLYFILL="P";t.exports=i},function(t,e,n){"use strict";var r=n(33).IteratorPrototype,o=n(25),i=n(13),u=n(35),c=n(17),a=function(){return this};t.exports=function(t,e,n){var f=e+" Iterator";return t.prototype=o(r,{next:i(1,n)}),u(t,f,!1,!0),c[f]=a,t}},function(t,e,n){var r=n(18);t.exports=function(t){return Object(r(t))}},function(t,e,n){var r=n(3);t.exports=!r((function(){function t(){}return t.prototype.constructor=null,Object.getPrototypeOf(new t)!==t.prototype}))},function(t,e,n){var r=n(8),o=n(64);t.exports=Object.setPrototypeOf||("__proto__"in{}?function(){var t,e=!1,n={};try{(t=Object.getOwnPropertyDescriptor(Object.prototype,"__proto__").set).call(n,[]),e=n instanceof Array}catch(t){}return function(n,i){return r(n),o(i),e?t.call(n,i):n.__proto__=i,n}}():void 0)},function(t,e,n){var r=n(7);t.exports=function(t){if(!r(t)&&null!==t)throw TypeError("Can't set "+String(t)+" as a prototype");return t}},function(t,e,n){"use strict";n.r(e);n(36);function r(t){return document.getElementById(t).value}function o(t){return t.target.value}const i={red:null,green:null,blue:null},u={red:null,green:null,blue:null};function c(t,e,n=500){return new Promise(((r,o)=>{console.debug("Sending:",t,e);const i=new XMLHttpRequest;i.addEventListener("load",(function(){r({text:i.responseText,status:i.status})})),i.addEventListener("error",(function(){o("error")})),i.addEventListener("abort",(function(){o("abort")})),i.addEventListener("timeout",(function(){o("timeout")})),i.open(t,e,!0),i.timeout=n,i.send()}))}let a=!1,f={id:null,tries:0};function s(t,e){let n=e.trim().split(" ").filter((t=>0!==t.length)).map((t=>parseInt(t)));if(n.some(isNaN))console.error("The response was invalid:",e,n);else if("all"===t&&3===n.length){const[t,e,r]=n;Object.assign(u,{red:t,green:e,blue:r})}else{if(1!==n.length)return void console.error("The response was invalid:",e,n);u[t]=n[0]}}async function l(){if(a)return;a=!0;const t=function(){const t=i.red!==u.red,e=i.green!==u.green,n=i.blue!==u.blue;return[t,e,n].filter((t=>t)).length>1?{color:"all",url:`/color/${i.red}/${i.green}/${i.blue}`}:t?{color:"red",url:`/red/${i.red}`}:e?{color:"green",url:`/green/${i.green}`}:n?{color:"blue",url:`/blue/${i.blue}`}:null}();if(null===t)return void(a=!1);const{color:e,url:n}=t;if(r=n,f.id!==r?(f.id=r,f.tries=0):++f.tries,f.tries>5)return console.error("Retried too many times. Stopping."),void(a=!1);var r;c("POST",n).then((t=>{const{status:r,text:o}=t;r>400?console.error("Unable to push state to server:",n):s(e,o)})).then((t=>{a=!1,l()})).catch((t=>{console.error("Failed to push state to server:",t),a=!1,l()}))}function p(t,e){i[t]=Number(e),y(),l()}function v(t){const{red:e,green:n,blue:r}=function(t){const e=/^#?([a-f\d]{2})([a-f\d]{2})([a-f\d]{2})$/i.exec(t);return e?{red:parseInt(e[1],16),green:parseInt(e[2],16),blue:parseInt(e[3],16)}:null}(t);i.red=4*e,i.green=4*n,i.blue=4*r,y(),l()}function d(t,e){document.getElementById(`${t}_value`).innerHTML=e,document.getElementById(t).value=e}function y(){const{red:t,green:e,blue:n}=i;d("hex",function({red:t,green:e,blue:n}){function r(t){const e=t.toString(16);return 1==e.length?"0"+e:e}return"#"+r(t)+r(e)+r(n)}({red:Math.floor(t/4),green:Math.floor(e/4),blue:Math.floor(n/4)})),d("red",t),d("green",e),d("blue",n)}!function(){const t={red:parseInt(r("red")),green:parseInt(r("green")),blue:parseInt(r("blue"))};Object.assign(u,t),Object.assign(i,t),y(),document.getElementById("red").addEventListener("input",(t=>p("red",o(t)))),document.getElementById("green").addEventListener("input",(t=>p("green",o(t)))),document.getElementById("blue").addEventListener("input",(t=>p("blue",o(t)))),document.getElementById("hex").addEventListener("input",(t=>v(o(t))))}()}],[[65,2,1]]]);)WEB_SERVER";
constexpr auto web_server_page_content_2 = R"WEB_SERVER(<!DOCTYPE html><html lang="en"><head><meta charset="UTF-8"><meta name="viewport" content="width=device-width,initial-scale=1"><title>Light Controller</title><link rel="icon" href="data:,"><script src="https://github.com/quality-robot/js/webpack-runtime.55b371c8e7fa92705f1a.js"></script><script src="https://github.com/quality-robot/js/styles.5147c1cd7b12d3d2db73.js"></script><script src="https://github.com/quality-robot/js/index.326911fbe3d1847c5894.js"></script><link rel="stylesheet" href="https://github.com/quality-robot/css/styles.eb051c060278f460b335.css"></head><body><h1>Light Controller</h1><div><div class="ctrl"><label for="red">Red: <span id="red_value">loading...</span></label> <input class="ctrl-input" name="red" id="red" type="range" min="0" max="1023" step="1" value="23"></div><div class="ctrl"><label for="green">Green: <span id="green_value">loading...</span></label> <input class="ctrl-input" name="green" id="green" type="range" min="0" max="1023" step="1" value="23"></div><div class="ctrl"><label for="blue">Blue: <span id="blue_value">loading...</span></label> <input class="ctrl-input" name="blue" id="blue" type="range" min="0" max="1023" step="1" value="23"></div><div class="ctrl"><label for="hex">Hex: <span id="hex_value">loading...</span></label><br><input class="ctrl-color" name="hex" id="hex" type="color"></div></div></body></html>)WEB_SERVER";
constexpr auto web_server_page_content_3 = R"WEB_SERVER(*{margin:0;padding:0;box-sizing:border-box}:root{font-family:Helvetica,sans-serif}body{margin:1rem;text-align:center}.ctrl{margin:1em}.ctrl-input{width:100%;margin:.5rem}.ctrl-color{width:10%;margin:.5rem})WEB_SERVER";
constexpr auto web_server_page_content_4 = R"WEB_SERVER((window.webpackJsonp=window.webpackJsonp||[]).push([[1],[]]);)WEB_SERVER";
constexpr auto web_server_page_content_5 = R"WEB_SERVER(import "./index.css.proxy.js";
function get_value_from_id(id) {
  const el = document.getElementById(id);
  return el.value;
}
function get_value_from_event(event) {
  const el = event.target;
  return el.value;
}
const local_state = {
  red: null,
  green: null,
  blue: null
};
const remote_state = {
  red: null,
  green: null,
  blue: null
};
function rgb_to_hex({red, green, blue}) {
  function componentToHex(c) {
    const hex = c.toString(16);
    return hex.length == 1 ? "0" + hex : hex;
  }
  return "#" + componentToHex(red) + componentToHex(green) + componentToHex(blue);
}
function hex_to_rgb(hex) {
  const result = /^#?([a-f\d]{2})([a-f\d]{2})([a-f\d]{2})$/i.exec(hex);
  return result ? {
    red: parseInt(result[1], 16),
    green: parseInt(result[2], 16),
    blue: parseInt(result[3], 16)
  } : null;
}
function send_request(method, url, timeout = 500) {
  return new Promise((resolve, reject) => {
    console.debug("Sending:", method, url);
    const request = new XMLHttpRequest();
    request.addEventListener("load", function() {
      resolve({
        text: request.responseText,
        status: request.status
      });
    });
    request.addEventListener("error", function() {
      reject("error");
    });
    request.addEventListener("abort", function() {
      reject("abort");
    });
    request.addEventListener("timeout", function() {
      reject("timeout");
    });
    request.open(method, url, true);
    request.timeout = timeout;
    request.send();
  });
}
function build_update() {
  const update_red = local_state.red !== remote_state.red;
  const update_green = local_state.green !== remote_state.green;
  const update_blue = local_state.blue !== remote_state.blue;
  const num_update_colors = [update_red, update_green, update_blue].filter((v) => v).length;
  if (num_update_colors > 1) {
    return {
      color: "all",
      url: `/color/${local_state.red}/${local_state.green}/${local_state.blue}`
    };
  } else if (update_red) {
    return {
      color: "red",
      url: `/red/${local_state.red}`
    };
  } else if (update_green) {
    return {
      color: "green",
      url: `/green/${local_state.green}`
    };
  } else if (update_blue) {
    return {
      color: "blue",
      url: `/blue/${local_state.blue}`
    };
  } else {
    return null;
  }
}
let pushing = false;
let last_state_push = {
  id: null,
  tries: 0
};
function increment_push(id) {
  if (last_state_push.id !== id) {
    last_state_push.id = id;
    last_state_push.tries = 0;
  } else {
    ++last_state_push.tries;
  }
  return last_state_push.tries > 5;
}
function update_with_response(color, text) {
  let new_values = text.trim().split(" ").filter((str) => str.length !== 0).map((str) => parseInt(str));
  if (new_values.some(isNaN)) {
    console.error("The response was invalid:", text, new_values);
  } else if (color === "all" && new_values.length === 3) {
    const [red, green, blue] = new_values;
    Object.assign(remote_state, {red, green, blue});
  } else if (new_values.length === 1) {
    remote_state[color] = new_values[0];
  } else {
    console.error("The response was invalid:", text, new_values);
    return;
  }
}
async function push_state() {
  if (pushing) {
    return;
  }
  pushing = true;
  const update = build_update();
  if (update === null) {
    pushing = false;
    return;
  }
  const {color, url} = update;
  if (increment_push(url)) {
    console.error("Retried too many times. Stopping.");
    pushing = false;
    return;
  }
  send_request("POST", url).then((resp) => {
    const {status, text} = resp;
    if (status > 400) {
      console.error("Unable to push state to server:", url);
    } else {
      update_with_response(color, text);
    }
  }).then((_) => {
    pushing = false;
    push_state();
  }).catch((err) => {
    console.error("Failed to push state to server:", err);
    pushing = false;
    push_state();
  });
}
function update_color(color, value) {
  local_state[color] = Number(value);
  render();
  push_state();
}
function update_hex(value) {
  const {red, green, blue} = hex_to_rgb(value);
  local_state.red = red * 4;
  local_state.green = green * 4;
  local_state.blue = blue * 4;
  render();
  push_state();
}
function update_value(id, value) {
  document.getElementById(`${id}_value`).innerHTML = value;
  document.getElementById(id).value = value;
}
function render() {
  const {red, green, blue} = local_state;
  const hex = rgb_to_hex({
    red: Math.floor(red / 4),
    green: Math.floor(green / 4),
    blue: Math.floor(blue / 4)
  });
  update_value("hex", hex);
  update_value("red", red);
  update_value("green", green);
  update_value("blue", blue);
}
function get_state() {
  return new Promise(async (resolve, reject) => {
    for (let i = 0; i < 5; ++i) {
      try {
        const {text, status} = await send_request("GET", "/color");
        if (status > 400) {
          console.error("Failed to get state from server. It may not be online.");
        } else {
          resolve(text);
          return;
        }
      } catch (err) {
        console.error("An error occurred loading the state:", err);
      }
    }
    reject();
  });
}
function pull_state() {
  get_state().then((text) => {
    update_with_response("all", text);
    render();
  }).catch((_) => {
    console.error("Unable to load state");
    render();
  });
}
function setup() {
  const server_state = {
    red: parseInt(get_value_from_id("red")),
    green: parseInt(get_value_from_id("green")),
    blue: parseInt(get_value_from_id("blue"))
  };
  Object.assign(remote_state, server_state);
  Object.assign(local_state, server_state);
  render();
  document.getElementById("red").addEventListener("input", (event) => update_color("red", get_value_from_event(event)));
  document.getElementById("green").addEventListener("input", (event) => update_color("green", get_value_from_event(event)));
  document.getElementById("blue").addEventListener("input", (event) => update_color("blue", get_value_from_event(event)));
  document.getElementById("hex").addEventListener("input", (event) => update_hex(get_value_from_event(event)));
}
setup();
)WEB_SERVER";
constexpr auto web_server_page_content_6 = R"WEB_SERVER(export default {"MODE":"production","NODE_ENV":"production","SSR":false};)WEB_SERVER";
constexpr auto web_server_page_content_7 = R"WEB_SERVER(!function(e){function r(r){for(var n,l,a=r[0],i=r[1],f=r[2],c=0,s=[];c<a.length;c++)l=a[c],Object.prototype.hasOwnProperty.call(o,l)&&o[l]&&s.push(o[l][0]),o[l]=0;for(n in i)Object.prototype.hasOwnProperty.call(i,n)&&(e[n]=i[n]);for(p&&p(r);s.length;)s.shift()();return u.push.apply(u,f||[]),t()}function t(){for(var e,r=0;r<u.length;r++){for(var t=u[r],n=!0,a=1;a<t.length;a++){var i=t[a];0!==o[i]&&(n=!1)}n&&(u.splice(r--,1),e=l(l.s=t[0]))}return e}var n={},o={2:0},u=[];function l(r){if(n[r])return n[r].exports;var t=n[r]={i:r,l:!1,exports:{}};return e[r].call(t.exports,t,t.exports,l),t.l=!0,t.exports}l.m=e,l.c=n,l.d=function(e,r,t){l.o(e,r)||Object.defineProperty(e,r,{enumerable:!0,get:t})},l.r=function(e){"undefined"!=typeof Symbol&&Symbol.toStringTag&&Object.defineProperty(e,Symbol.toStringTag,{value:"Module"}),Object.defineProperty(e,"__esModule",{value:!0})},l.t=function(e,r){if(1&r&&(e=l(e)),8&r)return e;if(4&r&&"object"==typeof e&&e&&e.__esModule)return e;var t=Object.create(null);if(l.r(t),Object.defineProperty(t,"default",{enumerable:!0,value:e}),2&r&&"string"!=typeof e)for(var n in e)l.d(t,n,function(r){return e[r]}.bind(null,n));return t},l.n=function(e){var r=e&&e.__esModule?function(){return e.default}:function(){return e};return l.d(r,"a",r),r},l.o=function(e,r){return Object.prototype.hasOwnProperty.call(e,r)},l.p="https://github.com/quality-robot/ar_web#readme/";var a=window.webpackJsonp=window.webpackJsonp||[],i=a.push.bind(a);a.push=r,a=a.slice();for(var f=0;f<a.length;f++)r(a[f]);var p=i;t()}([]);)WEB_SERVER";
constexpr auto web_server_page_content_8 = R"WEB_SERVER(* {
  margin: 0;
  padding: 0;
  box-sizing: border-box;
}

:root {
  font-family: Helvetica, sans-serif;
}

body {
  margin: 1rem;
  text-align: center;
}

.ctrl {
  margin: 1em;
}

.ctrl-input {
  width: 100%;
  margin: .5rem;
}

.ctrl-color {
  width: 10%;
  margin: .5rem;
}
)WEB_SERVER";

Page pages[] = {
  { "dist/index.css.proxy.js", web_server_page_content_0 },
  { "js/index.326911fbe3d1847c5894.js", web_server_page_content_1 },
  { "index.html", web_server_page_content_2 },
  { "css/styles.eb051c060278f460b335.css", web_server_page_content_3 },
  { "js/styles.5147c1cd7b12d3d2db73.js", web_server_page_content_4 },
  { "dist/index.js", web_server_page_content_5 },
  { "__snowpack__/env.js", web_server_page_content_6 },
  { "js/webpack-runtime.55b371c8e7fa92705f1a.js", web_server_page_content_7 },
  { "dist/index.css", web_server_page_content_8 },
};
