const path = require('path')
const config = require("../config")
const merge = require('webpack-merge')
const baseWebpackConfig = require('./webpack.base.js')
const webpack = require('webpack')
const uglify = require('uglifyjs-webpack-plugin')
process.env.NODE_ENV = 'production'

function assetsPath(_path) {
    return path.posix.join(config.build.version, _path)
}

const webpackConfig = merge(baseWebpackConfig, {
    mode: 'production',
    output: {
        path: config.build.assetsRoot,
        filename: assetsPath('js/[name].[chunkhash].js'),
        // chunkFilename: assetsPath('js/[id].[chunkhash].js')
    },
    // 插件, 用于生产模板和各项功能
    plugins:[
        new uglify(),
        new webpack.DefinePlugin({
            'process.env': process.env.NODE_ENV
        }),
    ]
})
module.exports = webpackConfig
