'use strict'
module.exports = {
  NODE_ENV: '"production"',
  // 测试环境发布流程 还是 线上环境发布流程目前有两种取值， 字符串 daily 和 publish
  RES_PATH: `'${process.env.SHARE_PATH ? "res" : "static"}'`,
  VERSION_PATH: `'${process.env.VERSION || "static"}'`,
  PUBLIC_PATH: `'${process.env.ASSETS_PATH || "//mail.qq.com"}'`
}
