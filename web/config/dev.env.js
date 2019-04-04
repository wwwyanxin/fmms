'use strict'
const merge = require('webpack-merge')
const prodEnv = require('./prod.env')

module.exports = merge(prodEnv, {
  NODE_ENV: '"development"',
  RES_PATH: '"static"',
  VERSION_PATH: '"static"',
  PUBLIC_PATH: '"//mail.qq.com"'
})
