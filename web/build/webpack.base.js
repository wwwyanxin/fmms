const path = require("path")
const glob = require("glob")
const utils = require("./utils")
const config = require("../config")

// css 代码抽取
const MiniCssExtractPlugin = require("mini-css-extract-plugin");
const CleanWebpackPlugin = require('clean-webpack-plugin')
//vue-loader@15.*之后除了必须带有VueLoaderPlugin之外，还需另外单独配置css-loader。
const VueLoaderPlugin = require('vue-loader/lib/plugin');



function resolve(dir) {
    return path.join(__dirname, '..', dir)
}
const assetsSubDirectory = process.env.NODE_ENV === 'production' ? config.build.assetsSubDirectory : config.dev.assetsSubDirectory


module.exports={
    // 入口文件的配置项
    entry:utils.entries(),
    output: {
        // 打包的路径
        path: config.build.assetsRoot,
        // 打包的文件名称
        filename: utils.assetsPath('js/[name].[hash:5].js'),
        // publicPath: 只要作用就是处理静态文件在html里的路径，一般也是用这个来指定上线后的cdn域名。
        publicPath:
            process.env.NODE_ENV === 'production'
                ? config.build.assetsPublicPath
                : config.dev.assetsPublicPath
    },

    // 将@自动映射为src
    resolve: {
        extensions: ['.js', '.vue', '.json'],
        modules: ['node_modules', resolve('src')],
        alias: {
            'vue$': 'vue/dist/vue.esm.js',
            '@': resolve('src')
        }
    },

    // 抽取公共的js
    optimization: {
        splitChunks: {
            cacheGroups: {
                vendor: { // 抽离第三方插件
                    test: /node_modules/,
                    chunks: 'initial',
                    name: 'common/vendor', // 打包后的文件名，任意命名
                    priority: 10 // 设置优先级，防止和自定义的公共代码提取时被覆盖，不进行打包
                },
                utils: { // 抽离自定义公共代码
                    test: /\.js$/,
                    chunks: 'initial',
                    name: 'common/utils',
                    minSize: 0 // 只要超出0字节就生成一个新包
                }
            }
        }
    },

    // 模块: 例如解读CSS, 图片如何转换,压缩
    module:{
        rules:[
            {
                test:/\.vue$/,
                use:{
                    loader: "vue-loader"
                }
            },
            {
                test:/\.(jsx|js)$/,
                use:{
                    loader: "babel-loader"
                },
                exclude: /node_modules/
            },
            //css loader
            {
                test:/\.css$/,
                use:[
                    MiniCssExtractPlugin.loader,// MiniCssExtractPlugin 抽取 css 注意:与style-loader冲突
                    // {loader:"style-loader"},
                    {
                        loader:"css-loader"
                    },
                    {
                        loader: 'postcss-loader',
                        options: {
                            config: {
                                // 必须要指定这个path，不然在deploy的时候，加载node_modules里面的css，类似quill.css时候，会提示找不到postconfig
                                path: path.resolve(__dirname, '../')
                            }
                        }
                    }
                ],
            },
            {
                test: /\.(png|jpe?g|gif|svg|cur)(\?.*)?$/,
                loader: 'file-loader',
                options: {
                    name: filePath => {
                        let sep = path.sep
                        let relative = filePath.replace(process.cwd(), '')
                            .replace(`src${sep}style${sep}images${sep}`, '')
                            .replace(`src${sep}`, '')
                            .replace(`images${sep}`, '')
                        let name = path.join(`${assetsSubDirectory}/images`, relative).replace(/\\/ig, '/')
                        let dirname = path.dirname(name)
                        // console.log('======================', dirname)
                        return `${dirname}/[name].[hash:7].[ext]`
                    }
                }
            },
            {
                test: /\.(mp4|webm|ogg|mp3|wav|flac|aac)(\?.*)?$/,
                loader: 'url-loader',
                options: {
                    limit: 10000,
                    name: utils.assetsPath('media/[name].[hash:7].[ext]')
                }
            },
            {
                test: /\.(woff2?|eot|ttf|otf)(\?.*)?$/,
                loader: 'url-loader',
                options: {
                    limit: 10000,
                    name: utils.assetsPath('fonts/[name].[hash:7].[ext]')
                }
            }
        ]
    },

    // 插件, 用于生产模板和各项功能
    plugins:[
        new VueLoaderPlugin(),
        new MiniCssExtractPlugin({
            filename: utils.assetsPath("css/[name].[hash:5].css"),
            chunkFilename: utils.assetsPath("css/[id].css")
        }),
        new CleanWebpackPlugin(['dist'], {
            root: path.join(__dirname,'..')
        }),
        ...utils.htmlPlugin()
    ]
}
