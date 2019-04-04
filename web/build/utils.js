'use strict'
const path = require('path')
const config = require('../config')
//const ExtractTextPlugin = require('extract-text-webpack-plugin')
const packageConfig = require('../package.json')

const assetsPath = exports.assetsPath = function(_path) {
    const assetsSubDirectory = process.env.NODE_ENV === 'production' ?
        config.build.assetsSubDirectory :
        config.dev.assetsSubDirectory
    return path.posix.join(assetsSubDirectory, _path)
}

exports.cssLoaders = function(options) {
    options = options || {}

    const cssLoader = {
        loader: 'css-loader',
        options: {
            sourceMap: options.sourceMap
        }
    }

    const postcssLoader = {
        loader: 'postcss-loader',
        options: {
            sourceMap: options.sourceMap,
            config: {
                // 必须要指定这个path，不然在deploy的时候，加载node_modules里面的css，类似quill.css时候，会提示找不到postconfig
                path: path.resolve(__dirname, '../')
            }
        }
    }

    // generate loader string to be used with extract text plugin
    function generateLoaders(loader, loaderOptions) {
        const loaders = options.usePostCSS ? [cssLoader, postcssLoader] : [cssLoader]

        if (loader) {
            loaders.push({
                loader: loader + '-loader',
                options: Object.assign({}, loaderOptions, {
                    sourceMap: options.sourceMap
                })
            })
        }

        // Extract CSS when that option is specified
        // (which is the case during production build)
        if (options.extract) {
            return ExtractTextPlugin.extract({
                use: loaders,
                fallback: 'vue-style-loader'
            })
        } else {
            return ['vue-style-loader'].concat(loaders)
        }
    }

    // https://vue-loader.vuejs.org/en/configurations/extract-css.html
    return {
        css: generateLoaders(),
        postcss: generateLoaders(),
        less: generateLoaders('less'),
        sass: generateLoaders('sass', {
            indentedSyntax: true
        }),
        scss: generateLoaders('sass'),
        stylus: generateLoaders('stylus'),
        styl: generateLoaders('stylus')
    }
}

/*// Generate loaders for standalone style files (outside of .vue)
exports.styleLoaders = function(options) {
    const output = []
    const loaders = exports.cssLoaders(options)

    for (const extension in loaders) {
        const loader = loaders[extension]
        output.push({
            test: new RegExp('\\.' + extension + '$'),
            use: loader,
            exclude: /iframe_wx\.css/i
        })
    }

    return output
}*/

/* 这里是添加的部分 ---------------------------- 开始 */

// glob是webpack安装时依赖的一个第三方模块，还模块允许你使用 *等符号, 例如lib/*.js就是获取lib文件夹下的所有js后缀名的文件
const glob = require('glob')
// 页面模板
const HtmlWebpackPlugin = require('html-webpack-plugin')
// 取得相应的页面路径，因为之前的配置，所以是src文件夹下的pages文件夹
const PAGE_PATH = path.resolve(__dirname, '../src/page')
// 用于做相应的merge处理
const merge = require('webpack-merge')

// 多入口配置
// 通过glob模块读取pages文件夹下的所有对应文件夹下的js后缀文件，如果该文件存在
// 那么就作为入口处理
exports.entries = function() {
    let entryFiles = glob.sync(PAGE_PATH + '/*/*.js')
    let map = {}
    entryFiles.forEach((filePath) => {
        let filename = filePath.substring(filePath.lastIndexOf('\/') + 1, filePath.lastIndexOf('.'))
        map[filename] = filePath
    })
    return map
}
const templateDirectory = process.env.NODE_ENV === 'production' ?
    config.build.templateDirectory : config.dev.templateDirectory
// 多页面输出配置
// 与上面的多页面入口配置相同，读取pages文件夹下的对应的html后缀文件，然后放入数组中
exports.htmlPlugin = function() {
    let entryHtml = glob.sync(PAGE_PATH + '/*/*.html')
    let arr = []
    entryHtml.forEach((filePath) => {
        let filename = filePath.substring(filePath.lastIndexOf('\/') + 1, filePath.lastIndexOf('.'))
        let conf = {
            // 模板来源
            template: filePath,
            // 文件名称
            filename: `${templateDirectory}/${filename}.html`,
            // 页面模板需要加对应的js脚本，如果不加这行则每个页面都会引入所有的js脚本
            chunks: ['common/utils', 'common/vendor', filename],
            // favicon: path.resolve(__dirname, '..', 'src/style/images/favicon/qqmail_favicon_32h.png'),
            inject: true
        }
        if (process.env.NODE_ENV === 'production') {
            conf = merge(conf, {
                minify: {
                    removeComments: true,
                    collapseWhitespace: true,
                    removeAttributeQuotes: true
                },
                chunksSortMode: 'dependency'
            })
        }
        arr.push(new HtmlWebpackPlugin(conf))
    })
    return arr
}
/* 这里是添加的部分 ---------------------------- 结束 */

// 多雪碧图输出配置
/*const SPRITES_PATH = path.resolve(__dirname, '../src/style/sprites/')
const WebpackSpritesmithPlugin = require('webpack-spritesmith')

exports.multipleSpritesPlugins = function() {
    let spritesDirs = glob.sync(SPRITES_PATH + '/!*!/')
    let arr = []
    spritesDirs.forEach((filePath) => {

        let dir = path.basename(filePath)
        // console.log(filePath, ',name:', dir)
        arr.push(new WebpackSpritesmithPlugin({
            // 目标小图标
            src: {
                // 图片所在文件夹（无视子文件夹）
                cwd: filePath,
                // 匹配 png 文件，可以用glob语法，比如 '*.(png|jpg)' 这样；
                // 但png和jpg拼一起，有时候图片无法正常显示
                glob: '*.png'
            },
            // 输出雪碧图文件及样式文件
            target: {
                // 将其输出到 src/assets 目录下
                // 这个是打包前的目录，所以不要学某个教程将其输出到 dist 目录下
                image: path.resolve(__dirname, `../src/style/images/sprites/${dir}.png`),
                // 可以是字符串、或者数组
                css: [
                    path.resolve(__dirname, `../src/style/css/sprites/${dir}.css`)
                ]
            },
            apiOptions: {
                generateSpriteName: function() {
                    // console.log('generateSpriteName arguments ------------------>', arguments)
                    // var fileName = arguments[0].match(/[^\\]+$/)[0].replace(/\.[a-zA-Z]+/, '')
                    const extName = path.extname(arguments[0])
                    const fileName = path.basename(arguments[0], extName)
                    // console.log(`ico_${dir}_${fileName}`)
                    return `${dir}-${fileName}`
                },
                // 简单来说，这个就是雪碧图的 css 文件怎么找到 雪碧图的 png 文件
                cssImageRef: `../../images/sprites/${dir}.png`
            },
            spritesmithOptions: {
                // 这个是雪碧图的排列顺序（从上到下）
                algorithm: 'left-right', // top-down
                // 雪碧图里，图片和图片的距离，单位是px
                padding: 20
            },
            retina: '@2x'
            // {
            //   classifier: imagePath => {
            //     console.log('------------>', imagePath)
            //     var fileName = imagePath.match(/[^\\]+$/)[0].replace(/\.[a-zA-Z]+/, '')
            //     const parsed = splitExt(imagePath);
            //     var suffix = '@2x'
            //     if (/@2x$/.test(fileName)) {
            //       return {
            //         type: 'retina',
            //         normalName: parsed.name.slice(0, -suffix.length) + parsed.ext,
            //         retinaName: imagePath
            //       }
            //     } else {
            //       return {
            //         type: 'normal',
            //         normalName: imagePath,
            //         retinaName: parsed.name + suffix + parsed.ext
            //       }
            //     }
            //   },
            //   targetImage: path.resolve(__dirname, `../src/style/images/sprites/${dir}@2x.png`),
            //   cssImageRef: `../../images/sprites/${dir}@2x.png`
            // }
        }))
    })
    return arr
}*/

// const splitExt = (fileName) => {
//   const extInd = fileName.lastIndexOf('.');
//   return {
//     name: fileName.slice(0, extInd),
//     ext: fileName.slice(extInd)
//   };
// };

/* 这里是添加的部分 ---------------------------- 结束 */

/*exports.createNotifierCallback = () => {
    const notifier = require('node-notifier')

    return (severity, errors) => {
        if (severity !== 'error') return

        const error = errors[0]
        const filename = error.file && error.file.split('!').pop()

        notifier.notify({
            title: packageConfig.name,
            message: severity + ': ' + error.name,
            subtitle: filename || '',
            icon: path.join(__dirname, 'logo.png')
        })
    }
}*/
