struct Page {
  const char* const filename;
  const char* const content;
};

constexpr auto web_server_page_content_0 = R"WEB_SERVER(!function(e){function r(r){for(var n,l,f=r[0],i=r[1],a=r[2],c=0,s=[];c<f.length;c++)l=f[c],Object.prototype.hasOwnProperty.call(o,l)&&o[l]&&s.push(o[l][0]),o[l]=0;for(n in i)Object.prototype.hasOwnProperty.call(i,n)&&(e[n]=i[n]);for(p&&p(r);s.length;)s.shift()();return u.push.apply(u,a||[]),t()}function t(){for(var e,r=0;r<u.length;r++){for(var t=u[r],n=!0,f=1;f<t.length;f++){var i=t[f];0!==o[i]&&(n=!1)}n&&(u.splice(r--,1),e=l(l.s=t[0]))}return e}var n={},o={2:0},u=[];function l(r){if(n[r])return n[r].exports;var t=n[r]={i:r,l:!1,exports:{}};return e[r].call(t.exports,t,t.exports,l),t.l=!0,t.exports}l.m=e,l.c=n,l.d=function(e,r,t){l.o(e,r)||Object.defineProperty(e,r,{enumerable:!0,get:t})},l.r=function(e){"undefined"!=typeof Symbol&&Symbol.toStringTag&&Object.defineProperty(e,Symbol.toStringTag,{value:"Module"}),Object.defineProperty(e,"__esModule",{value:!0})},l.t=function(e,r){if(1&r&&(e=l(e)),8&r)return e;if(4&r&&"object"==typeof e&&e&&e.__esModule)return e;var t=Object.create(null);if(l.r(t),Object.defineProperty(t,"default",{enumerable:!0,value:e}),2&r&&"string"!=typeof e)for(var n in e)l.d(t,n,function(r){return e[r]}.bind(null,n));return t},l.n=function(e){var r=e&&e.__esModule?function(){return e.default}:function(){return e};return l.d(r,"a",r),r},l.o=function(e,r){return Object.prototype.hasOwnProperty.call(e,r)},l.p="/";var f=window.webpackJsonp=window.webpackJsonp||[],i=f.push.bind(f);f.push=r,f=f.slice();for(var a=0;a<f.length;a++)r(f[a]);var p=i;t()}([]);)WEB_SERVER";
constexpr auto web_server_page_content_1 = R"WEB_SERVER(* {
  font: 1em sans-serif;
}

div#root {
  color: black;
  margin: 1rem;
  font-size: xx-large;
}
)WEB_SERVER";
constexpr auto web_server_page_content_2 = R"WEB_SERVER((window.webpackJsonp=window.webpackJsonp||[]).push([[1],[]]);)WEB_SERVER";
constexpr auto web_server_page_content_3 = R"WEB_SERVER(<!DOCTYPE html><html lang="en"><head><meta charset="UTF-8"><meta name="viewport" content="width=device-width,initial-scale=1"><title>My App</title><script src="/js/webpack-runtime.e8bdcdb7228880ee84fa.js"></script><script src="/js/styles.5147c1cd7b12d3d2db73.js"></script><script src="/js/index.39c334ade41900140b71.js"></script><link rel="stylesheet" href="/css/styles.80f71eecbecc6c47fcc7.css"></head><body><div id="root"></div></body></html>)WEB_SERVER";
constexpr auto web_server_page_content_4 = R"WEB_SERVER((window.webpackJsonp=window.webpackJsonp||[]).push([[0],[function(n,o,e){"use strict";e.r(o);document.getElementById("root").innerHTML="Hello, world!"}],[[0,2,1]]]);)WEB_SERVER";
constexpr auto web_server_page_content_5 = R"WEB_SERVER(export default {"MODE":"production","NODE_ENV":"production","SSR":false};)WEB_SERVER";
constexpr auto web_server_page_content_6 = R"WEB_SERVER(*{font:1em sans-serif}div#root{color:#000;margin:1rem;font-size:xx-large})WEB_SERVER";
constexpr auto web_server_page_content_7 = R"WEB_SERVER(import "./index.css.proxy.js";
const msg = "Hello, world!";
document.getElementById("root").innerHTML = msg;
)WEB_SERVER";
constexpr auto web_server_page_content_8 = R"WEB_SERVER(// [snowpack] add styles to the page (skip if no document exists)
if (typeof document !== 'undefined') {
  const code = "* {\n  font: 1em sans-serif;\n}\n\ndiv#root {\n  color: black;\n  margin: 1rem;\n  font-size: xx-large;\n}\n";

  const styleEl = document.createElement("style");
  const codeEl = document.createTextNode(code);
  styleEl.type = 'text/css';
  styleEl.appendChild(codeEl);
  document.head.appendChild(styleEl);
})WEB_SERVER";

Page pages[] = {
  { "build/js/webpack-runtime.e8bdcdb7228880ee84fa.js", web_server_page_content_0 },
  { "build/dist/index.css", web_server_page_content_1 },
  { "build/js/styles.5147c1cd7b12d3d2db73.js", web_server_page_content_2 },
  { "build/index.html", web_server_page_content_3 },
  { "build/js/index.39c334ade41900140b71.js", web_server_page_content_4 },
  { "build/__snowpack__/env.js", web_server_page_content_5 },
  { "build/css/styles.80f71eecbecc6c47fcc7.css", web_server_page_content_6 },
  { "build/dist/index.js", web_server_page_content_7 },
  { "build/dist/index.css.proxy.js", web_server_page_content_8 },
};
