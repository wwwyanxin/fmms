const blacklistConfig = require('./blacklistConfig')
const blacklistName = blacklistConfig.blacklistName
const blacklistNameSet = new Set(blacklistName)

let blacklistMap = null

function getBlacklistMap(topics) {
    // 缓存
    if (blacklistMap) {
        return blacklistMap
    }
    blacklistMap = new Map();
    for (const topic of topics) {
        if (blacklistNameSet.has(topic.sourcename)) {
            blacklistMap.set(topic.id, {
                "id": topic.id,
                "sourceid": topic.sourceid,
                "sourcename": topic.sourcename
            })
        }
    }
    return blacklistMap
}

export {
     getBlacklistMap
}
