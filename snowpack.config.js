const api_url = process.env.API_URL;
let routes = [];
if (api_url != null && api_url !== "") {
  const http_proxy = require('http-proxy');
  const proxy = http_proxy.createServer({ target: api_url });
  routes = [
    {
      src: '/api/.*',
      dest: (req, res) => {
        proxy.web(req, res);
      }
    },
  ];
}

module.exports = {
  routes,
  mount: {
    "ui/public/": '/',
    "ui/src/": '/dist',
  },
  buildOptions: {
    out: 'data',
    clean: true,
  },
  optimize: {
    bundle: true,
    minify: true,
    treeshake: true,
    splitting: true,
    //target: 'es2018',
  },
};
