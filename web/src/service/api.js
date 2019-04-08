import axios from 'axios'
import qs from 'qs'
import global from './global'
// import errorMsgConfig from '@/config/errorMsgConfig'

/*if (process.env.NODE_ENV !== 'production') {
    require('@/mock/mock.js')
}*/

const baseHost = ''
const cgiURL = baseHost + '/fmms/cgi-bin/logicsvr.cgi'

const CGIInstance = axios.create({
    baseURL: cgiURL
})

// CGIInstance.defaults.headers.post['Content-Type'] = 'application/x-www-form-urlencoded'
CGIInstance.defaults.headers.post['Content-Type'] = 'application/json'

function getRandomString() {
    return parseInt(Math.random() * 10000000000000) + '' + Date.now()
}

function getCGIRequestParams(params) {
    // const globalData = window.globalData // 这里先假设页面直出的时候会把sid, alias这些全局数据打在页面上
/*    const sid = global.get('sid')
    return Object.assign(
        {
            sid: sid,
            r: getRandomString()
        },
        params
    )*/
    return {...params}
}

function processCGIRequest(res, cgiName, config) {
    const app = global.get('app')
    if (!res || !res.data) {
        app.$message({
            type: 'error',
            message: '接口请求失败'
        })
        return null
    } else {
        return res.data
    }
}

const CGIClient = {
    async get(cgiName, params, config) {
        try {
            const res = await CGIInstance.get(cgiName, {
                params: getCGIRequestParams(params)
            })
            if (config && config.slient) {
                if (res && res.data) {
                    return res.data
                } else {
                    return null
                }
            } else {
                return processCGIRequest(res, cgiName, config)
            }
        } catch (CGIClientError) {
            console.log(CGIClientError)
            throw CGIClientError
            return null
        }
    },
    async post(cgiName, data, config) {
        try {
            let res = await CGIInstance.post(cgiName, data, {
                params: getCGIRequestParams(data.params || {}),
                transformRequest: [
                    function (data, headers) {
                        return typeof data === 'string'
                            ? data
                            : qs.stringify(data, {
                                arrayFormat: 'repeat'
                            })
                    }
                ]
            })
            if (config && config.slient) {
                if (res && res.data) {
                    return res.data
                } else {
                    return null
                }
            } else {
                return processCGIRequest(res, cgiName, config)
            }
        } catch (CGIClientError) {
            console.log(CGIClientError)
            throw CGIClientError
            return null
        }
    },
    isSuccessRawResponse(res) {
        // return res && (res.RetCode === 0 || (res.data && res.data.head.ret === 0))
        return res && res.data && res.data.head && res.data.head.ret === 0
    },
    isSuccessResponse(res) {
        return !!res
    }
}

export default CGIClient
