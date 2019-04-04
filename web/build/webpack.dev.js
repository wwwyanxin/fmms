const merge = require('webpack-merge')
const path = require('path')
const baseWebpackConfig = require('./webpack.base.js')
const webpack = require('webpack')


process.env.NODE_ENV = 'development'

const webpackConfig = merge(baseWebpackConfig, {
    mode: 'development',
    devtool: 'source-map',
    plugins:[
        new webpack.DefinePlugin({
            'process.env': process.env.NODE_ENV
        }),
    ],

    // 配置webpack开发服务功能
    devServer:{
        // 设计基本目录结构
        contentBase:path.resolve(__dirname, '../dist'),
        // 服务器的IP地址
        host:'localhost',
        // 服务端压缩是否开启
        compress:true,
        //配置服务端口
        port:8085
    }
})
module.exports = webpackConfig
