const globalData = {}

const set = (...args) => {
  if (typeof args[0] === 'string' && args.length === 2) {
    globalData[args[0]] = args[1]
  } else if (typeof args[0] === 'object') {
    Object.assign(globalData, args[0])
  }
}

const get = key => {
  if (key) {
    return globalData[key]
  } else {
    return globalData
  }
}

export default {
  set,
  get
}
