// Built by eustia.
"use strict";

var _ = {};

/* ------------------------------ inherits ------------------------------ */

export var inherits = _.inherits = (function () {
    /* Inherit the prototype methods from one constructor into another.
     *
     * |Name      |Type    |Desc       |
     * |----------|--------|-----------|
     * |Class     |function|Child Class|
     * |SuperClass|function|Super Class|
     *
     * ```javascript
     * function People(name)
     * {
     *     this._name = name;
     * }
     * People.prototype = {
     *     getName: function ()
     *     {
     *         return this._name;
     *     }
     * };
     * function Student(name)
     * {
     *     this._name = name;
     * }
     * inherits(Student, People);
     * var s = new Student('RedHood');
     * s.getName(); // -> 'RedHood'
     * ```
     */

    /* module
     * env: all
     * test: all
     */

    function exports(Class, SuperClass) {
        if (objCreate) return (Class.prototype = objCreate(SuperClass.prototype));

        noop.prototype = SuperClass.prototype;
        Class.prototype = new noop();
    }

    var objCreate = Object.create;

    function noop() {}

    return exports;
})();

/* ------------------------------ isBrowser ------------------------------ */

export var isBrowser = _.isBrowser = (function (exports) {
    /* Check if running in a browser.
     *
     * ```javascript
     * console.log(isBrowser); // -> true if running in a browser
     * ```
     */

    /* module
     * env: all
     * test: all
     */

    exports =
        typeof window === 'object' &&
        typeof document === 'object' &&
        document.nodeType === 9;

    return exports;
})({});

/* ------------------------------ allKeys ------------------------------ */

export var allKeys = _.allKeys = (function () {
    /* Retrieve all the names of object's own and inherited properties.
     *
     * |Name  |Type  |Desc                       |
     * |------|------|---------------------------|
     * |obj   |object|Object to query            |
     * |return|array |Array of all property names|
     *
     * > Members of Object's prototype won't be retrieved.
     *
     * ```javascript
     * var obj = Object.create({zero: 0});
     * obj.one = 1;
     * allKeys(obj) // -> ['zero', 'one']
     * ```
     */

    /* module
     * env: all
     * test: all
     */

    function exports(obj) {
        var ret = [],
            key;

        for (key in obj) ret.push(key);

        return ret;
    }

    return exports;
})();

/* ------------------------------ has ------------------------------ */

export var has = _.has = (function () {
    /* Checks if key is a direct property.
     *
     * |Name  |Type   |Desc                            |
     * |------|-------|--------------------------------|
     * |obj   |object |Object to query                 |
     * |key   |string |Path to check                   |
     * |return|boolean|True if key is a direct property|
     *
     * ```javascript
     * has({one: 1}, 'one'); // -> true
     * ```
     */

    /* module
     * env: all
     * test: all
     */

    var hasOwnProp = Object.prototype.hasOwnProperty;

    function exports(obj, key) {
        return hasOwnProp.call(obj, key);
    }

    return exports;
})();

/* ------------------------------ isObj ------------------------------ */

export var isObj = _.isObj = (function () {
    /* Check if value is the language type of Object.
     *
     * |Name  |Type   |Desc                      |
     * |------|-------|--------------------------|
     * |val   |*      |Value to check            |
     * |return|boolean|True if value is an object|
     *
     * [Language Spec](http://www.ecma-international.org/ecma-262/6.0/#sec-ecmascript-language-types)
     *
     * ```javascript
     * isObj({}); // -> true
     * isObj([]); // -> true
     * ```
     */

    /* module
     * env: all
     * test: all
     */

    function exports(val) {
        var type = typeof val;

        return !!val && (type === 'function' || type === 'object');
    }

    return exports;
})();

/* ------------------------------ isUndef ------------------------------ */

export var isUndef = _.isUndef = (function () {
    /* Check if value is undefined.
     *
     * |Name  |Type   |Desc                      |
     * |------|-------|--------------------------|
     * |val   |*      |Value to check            |
     * |return|boolean|True if value is undefined|
     *
     * ```javascript
     * isUndef(void 0); // -> true
     * isUndef(null); // -> false
     * ```
     */

    /* module
     * env: all
     * test: all
     */

    function exports(val) {
        return val === void 0;
    }

    return exports;
})();

/* ------------------------------ toStr ------------------------------ */

export var toStr = _.toStr = (function () {
    /* Convert value to a string.
     *
     * |Name  |Type  |Desc            |
     * |------|------|----------------|
     * |val   |*     |Value to convert|
     * |return|string|Resulted string |
     *
     * ```javascript
     * toStr(null); // -> ''
     * toStr(1); // -> '1'
     * toStr(false); // -> 'false'
     * toStr([1, 2, 3]); // -> '1,2,3'
     * ```
     */

    /* module
     * env: all
     * test: all
     */

    function exports(val) {
        return val == null ? '' : val.toString();
    }

    return exports;
})();

/* ------------------------------ debounce ------------------------------ */

export var debounce = _.debounce = (function () {
    /* Return a new debounced version of the passed function.
     *
     * |Name  |Type    |Desc                           |
     * |------|--------|-------------------------------|
     * |fn    |function|Function to debounce           |
     * |wait  |number  |Number of milliseconds to delay|
     * |return|function|New debounced function         |
     *
     * ```javascript
     * $(window).resize(debounce(calLayout, 300));
     * ```
     */

    /* module
     * env: all
     * test: all
     */

    function exports(fn, wait, immediate) {
        var timeout;

        return function() {
            var ctx = this,
                args = arguments;

            var throttler = function() {
                timeout = null;
                fn.apply(ctx, args);
            };

            if (!immediate) clearTimeout(timeout);
            if (!immediate || !timeout) timeout = setTimeout(throttler, wait);
        };
    }

    return exports;
})();

/* ------------------------------ root ------------------------------ */

export var root = _.root = (function (exports) {
    /* Root object reference, `global` in nodeJs, `window` in browser. */

    /* module
     * env: all
     * test: all
     */

    /* dependencies
     * isBrowser 
     */

    exports = isBrowser ? window : global;

    return exports;
})({});

/* ------------------------------ detectMocha ------------------------------ */

export var detectMocha = _.detectMocha = (function () {
    /* Detect if mocha is running.
     *
     * ```javascript
     * detectMocha(); // -> True if mocha is running.
     * ```
     */

    /* module
     * env: all
     * test: all
     */

    /* dependencies
     * root 
     */

    function exports() {
        for (var i = 0, len = methods.length; i < len; i++) {
            var method = methods[i];

            if (typeof root[method] !== 'function') return false;
        }

        return true;
    }

    var methods = ['afterEach', 'after', 'beforeEach', 'before', 'describe', 'it'];

    return exports;
})();

/* ------------------------------ keys ------------------------------ */

export var keys = _.keys = (function (exports) {
    /* Create an array of the own enumerable property names of object.
     *
     * |Name  |Type  |Desc                   |
     * |------|------|-----------------------|
     * |obj   |object|Object to query        |
     * |return|array |Array of property names|
     * 
     * ```javascript
     * keys({a: 1}); // -> ['a']
     * ```
     */

    /* module
     * env: all
     * test: all
     */

    /* dependencies
     * has detectMocha 
     */

    if (Object.keys && !detectMocha()) {
        exports = Object.keys;
    } else {
        exports = function(obj) {
            var ret = [],
                key;

            for (key in obj) {
                if (has(obj, key)) ret.push(key);
            }

            return ret;
        };
    }

    return exports;
})({});

/* ------------------------------ optimizeCb ------------------------------ */

export var optimizeCb = _.optimizeCb = (function () {
    /* Used for function context binding.
     */

    /* module
     * env: all
     * test: all
     */

    /* dependencies
     * isUndef 
     */

    function exports(fn, ctx, argCount) {
        if (isUndef(ctx)) return fn;

        switch (argCount == null ? 3 : argCount) {
            case 1:
                return function(val) {
                    return fn.call(ctx, val);
                };
            case 3:
                return function(val, idx, collection) {
                    return fn.call(ctx, val, idx, collection);
                };
            case 4:
                return function(accumulator, val, idx, collection) {
                    return fn.call(ctx, accumulator, val, idx, collection);
                };
        }

        return function() {
            return fn.apply(ctx, arguments);
        };
    }

    return exports;
})();

/* ------------------------------ escape ------------------------------ */

export var escape = _.escape = (function () {
    /* Escapes a string for insertion into HTML, replacing &, <, >, ", `, and ' characters.
     *
     * |Name  |Type  |Desc            |
     * |------|------|----------------|
     * |str   |string|String to escape|
     * |return|string|Escaped string  |
     *
     * ```javascript
     * escape('You & Me'); -> // -> 'You &amp; Me'
     * ```
     */

    /* module
     * env: all
     * test: all
     */

    /* dependencies
     * keys 
     */

    function exports(str) {
        return regTest.test(str) ? str.replace(regReplace, replaceFn) : str;
    }

    var map = (exports.map = {
        '&': '&amp;',
        '<': '&lt;',
        '>': '&gt;',
        '"': '&quot;',
        "'": '&#x27;',
        '`': '&#x60;'
    });

    var regSrc = '(?:' + keys(map).join('|') + ')',
        regTest = new RegExp(regSrc),
        regReplace = new RegExp(regSrc, 'g');

    function replaceFn(match) {
        return map[match];
    }

    return exports;
})();

/* ------------------------------ formatFileSize ------------------------------ */

export var formatFileSize = _.formatFileSize = (function () {
    function exports(bytes) {
      let unit = ''
      let formatSize = 0

      if (bytes < 1024) {
        unit = 'B'
        formatSize = bytes
      }else if (bytes / 1024 < 1024) {
        unit = 'K'
        formatSize = bytes / 1024
      } else if (bytes / 1024 / 1024 < 1024) {
        unit = 'M'
        formatSize = bytes / 1024 / 1024
      } else {
        unit = 'G'
        formatSize = bytes / 1024 / 1024 / 1024
      }

      return Math.round(formatSize * 100) / 100  + unit
    }

    return exports;
})();

/* ------------------------------ formatRemainTime ------------------------------ */

export var formatRemainTime = _.formatRemainTime = (function () {
    /* eslint-disable */
    function exports(seconds) {
      let hours = Math.floor(seconds / 3600)
      let mins = Math.floor((seconds / 60) % 60)
      let secs = Math.floor(seconds % 60)

      hours = hours < 9 ? `0${hours}` : hours
      mins = mins < 9 ? `0${mins}` : mins
      secs = secs < 9 ? `0${secs}` : secs

      return `${hours}:${mins}:${secs}`
    }

    return exports;
})();

/* ------------------------------ getResPath ------------------------------ */

export var getResPath = _.getResPath = (function () {
    function exports(path) {
      if (/^\/\//.test(path)) {
        return 'https:' + path
      } else {
        return 'http://mail.qq.com' + path
      }
    }

    return exports;
})();

/* ------------------------------ identity ------------------------------ */

export var identity = _.identity = (function () {
    /* Return the first argument given.
     *
     * |Name  |Type|Desc       |
     * |------|----|-----------|
     * |val   |*   |Any value  |
     * |return|*   |Given value|
     *
     * ```javascript
     * identity('a'); // -> 'a'
     * ```
     */

    /* module
     * env: all
     * test: all
     */

    function exports(val) {
        return val;
    }

    return exports;
})();

/* ------------------------------ objToStr ------------------------------ */

export var objToStr = _.objToStr = (function () {
    /* Alias of Object.prototype.toString.
     *
     * |Name  |Type  |Desc                                |
     * |------|------|------------------------------------|
     * |value |*     |Source value                        |
     * |return|string|String representation of given value|
     * 
     * ```javascript
     * objToStr(5); // -> '[object Number]'
     * ```
     */

    /* module
     * env: all
     * test: all
     */

    var ObjToStr = Object.prototype.toString;

    function exports(val) {
        return ObjToStr.call(val);
    }

    return exports;
})();

/* ------------------------------ isArgs ------------------------------ */

export var isArgs = _.isArgs = (function () {
    /* Check if value is classified as an arguments object.
     *
     * |Name  |Type   |Desc                                |
     * |------|-------|------------------------------------|
     * |val   |*      |Value to check                      |
     * |return|boolean|True if value is an arguments object|
     *
     * ```javascript
     * (function () {
     *     isArgs(arguments); // -> true
     * })();
     * ```
     */

    /* module
     * env: all
     * test: all
     */

    /* dependencies
     * objToStr 
     */

    function exports(val) {
        return objToStr(val) === '[object Arguments]';
    }

    return exports;
})();

/* ------------------------------ isArr ------------------------------ */

export var isArr = _.isArr = (function (exports) {
    /* Check if value is an `Array` object.
     *
     * |Name  |Type   |Desc                              |
     * |------|-------|----------------------------------|
     * |val   |*      |Value to check                    |
     * |return|boolean|True if value is an `Array` object|
     *
     * ```javascript
     * isArr([]); // -> true
     * isArr({}); // -> false
     * ```
     */

    /* module
     * env: all
     * test: all
     */

    /* dependencies
     * objToStr 
     */

    exports =
        Array.isArray ||
        function(val) {
            return objToStr(val) === '[object Array]';
        };

    return exports;
})({});

/* ------------------------------ castPath ------------------------------ */

export var castPath = _.castPath = (function () {
    /* Cast value into a property path array.
     *
     * |Name  |Type  |Desc               |
     * |------|------|-------------------|
     * |str   |*     |Value to inspect   |
     * |[obj] |object|Object to query    |
     * |return|array |Property path array|
     * 
     * ```javascript
     * castPath('a.b.c'); // -> ['a', 'b', 'c']
     * castPath(['a']); // -> ['a']
     * castPath('a[0].b'); // -> ['a', '0', 'b']
     * castPath('a.b.c', {'a.b.c': true}); // -> ['a.b.c']
     * ```
     */

    /* module
     * env: all
     * test: all
     */

    /* dependencies
     * has isArr 
     */

    function exports(str, obj) {
        if (isArr(str)) return str;
        if (obj && has(obj, str)) return [str];

        var ret = [];

        str.replace(regPropName, function(match, number, quote, str) {
            ret.push(quote ? str.replace(regEscapeChar, '$1') : number || match);
        });

        return ret;
    }

    // Lodash _stringToPath
    var regPropName = /[^.[\]]+|\[(?:(-?\d+(?:\.\d+)?)|(["'])((?:(?!\2)[^\\]|\\.)*?)\2)\]|(?=(?:\.|\[\])(?:\.|\[\]|$))/g,
        regEscapeChar = /\\(\\)?/g;

    return exports;
})();

/* ------------------------------ safeGet ------------------------------ */

export var safeGet = _.safeGet = (function () {
    /* Get object property, don't throw undefined error.
     *
     * |Name  |Type        |Desc                     |
     * |------|------------|-------------------------|
     * |obj   |object      |Object to query          |
     * |path  |array string|Path of property to get  |
     * |return|*           |Target value or undefined|
     *
     * ```javascript
     * var obj = {a: {aa: {aaa: 1}}};
     * safeGet(obj, 'a.aa.aaa'); // -> 1
     * safeGet(obj, ['a', 'aa']); // -> {aaa: 1}
     * safeGet(obj, 'a.b'); // -> undefined
     * ```
     */

    /* module
     * env: all
     * test: all
     */

    /* dependencies
     * isUndef castPath 
     */

    function exports(obj, path) {
        path = castPath(path, obj);

        var prop;

        prop = path.shift();
        while (!isUndef(prop)) {
            obj = obj[prop];
            if (obj == null) return;
            prop = path.shift();
        }

        return obj;
    }

    return exports;
})();

/* ------------------------------ isDate ------------------------------ */

export var isDate = _.isDate = (function () {
    /* Check if value is classified as a Date object.
     *
     * |Name  |Type   |Desc                          |
     * |------|-------|------------------------------|
     * |val   |*      |value to check                |
     * |return|boolean|True if value is a Date object|
     *
     * ```javascript
     * isDate(new Date()); // -> true
     * ```
     */

    /* module
     * env: all
     * test: all
     */

    /* dependencies
     * objToStr 
     */

    function exports(val) {
        return objToStr(val) === '[object Date]';
    }

    return exports;
})();

/* ------------------------------ isFn ------------------------------ */

export var isFn = _.isFn = (function () {
    /* Check if value is a function.
     *
     * |Name  |Type   |Desc                       |
     * |------|-------|---------------------------|
     * |val   |*      |Value to check             |
     * |return|boolean|True if value is a function|
     *
     * Generator function is also classified as true.
     *
     * ```javascript
     * isFn(function() {}); // -> true
     * isFn(function*() {}); // -> true
     * ```
     */

    /* module
     * env: all
     * test: all
     */

    /* dependencies
     * objToStr 
     */

    function exports(val) {
        var objStr = objToStr(val);

        return (
            objStr === '[object Function]' ||
            objStr === '[object GeneratorFunction]'
        );
    }

    return exports;
})();

/* ------------------------------ isMiniProgram ------------------------------ */

export var isMiniProgram = _.isMiniProgram = (function (exports) {
    /* Check if running in wechat mini program.
     *
     * ```javascript
     * console.log(isMiniProgram); // -> true if running in mini program.
     * ```
     */

    /* module
     * env: all
     * test: all
     */

    /* dependencies
     * isFn 
     */

    /* eslint-disable no-undef */
    exports = typeof wx !== 'undefined' && isFn(wx.openLocation);

    return exports;
})({});

/* ------------------------------ isPlainObj ------------------------------ */

export var isPlainObj = _.isPlainObj = (function () {
    /* Check if value is an object created by Object constructor.
     *
     * |Name  |Type   |Desc                           |
     * |------|-------|-------------------------------|
     * |val   |*      |Value to check                 |
     * |return|boolean|True if value is a plain object|
     *
     * ```javascript
     * isPlainObj({}); // -> true
     * isPlainObj([]); // -> false
     * isPlainObj(function () {}); // -> false
     * ```
     */

    /* module
     * env: all
     * test: all
     */

    /* dependencies
     * isObj isArr isFn has 
     */

    function exports(val) {
        if (!isObj(val)) return false;

        var ctor = val.constructor;
        if (!isFn(ctor)) return false;
        if (!has(ctor.prototype, 'isPrototypeOf')) return false;

        return !isArr(val) && !isFn(val);
    }

    return exports;
})();

/* ------------------------------ isStr ------------------------------ */

export var isStr = _.isStr = (function () {
    /* Check if value is a string primitive.
     *
     * |Name  |Type   |Desc                               |
     * |------|-------|-----------------------------------|
     * |val   |*      |Value to check                     |
     * |return|boolean|True if value is a string primitive|
     *
     * ```javascript
     * isStr('licia'); // -> true
     * ```
     */

    /* module
     * env: all
     * test: all
     */

    /* dependencies
     * objToStr 
     */

    function exports(val) {
        return objToStr(val) === '[object String]';
    }

    return exports;
})();

/* ------------------------------ isNum ------------------------------ */

export var isNum = _.isNum = (function () {
    /* Check if value is classified as a Number primitive or object.
     *
     * |Name  |Type   |Desc                                 |
     * |------|-------|-------------------------------------|
     * |val   |*      |Value to check                       |
     * |return|boolean|True if value is correctly classified|
     * 
     * ```javascript
     * isNum(5); // -> true
     * isNum(5.1); // -> true
     * isNum({}); // -> false
     * ```
     */

    /* module
     * env: all
     * test: all
     */

    /* dependencies
     * objToStr 
     */

    function exports(val) {
        return objToStr(val) === '[object Number]';
    }

    return exports;
})();

/* ------------------------------ isArrLike ------------------------------ */

export var isArrLike = _.isArrLike = (function () {
    /* Check if value is array-like.
     *
     * |Name  |Type   |Desc                       |
     * |------|-------|---------------------------|
     * |val   |*      |Value to check             |
     * |return|boolean|True if value is array like|
     *
     * > Function returns false.
     *
     * ```javascript
     * isArrLike('test'); // -> true
     * isArrLike(document.body.children); // -> true;
     * isArrLike([1, 2, 3]); // -> true
     * ```
     */

    /* module
     * env: all
     * test: all
     */

    /* dependencies
     * isNum isFn 
     */

    var MAX_ARR_IDX = Math.pow(2, 53) - 1;

    function exports(val) {
        if (!val) return false;

        var len = val.length;

        return isNum(len) && len >= 0 && len <= MAX_ARR_IDX && !isFn(val);
    }

    return exports;
})();

/* ------------------------------ each ------------------------------ */

export var each = _.each = (function () {
    /* Iterate over elements of collection and invokes iteratee for each element.
     *
     * |Name    |Type        |Desc                          |
     * |--------|------------|------------------------------|
     * |obj     |object array|Collection to iterate over    |
     * |iteratee|function    |Function invoked per iteration|
     * |[ctx]   |*           |Function context              |
     *
     * ```javascript
     * each({'a': 1, 'b': 2}, function (val, key) {});
     * ```
     */

    /* module
     * env: all
     * test: all
     */

    /* dependencies
     * isArrLike keys optimizeCb 
     */

    function exports(obj, iteratee, ctx) {
        iteratee = optimizeCb(iteratee, ctx);

        var i, len;

        if (isArrLike(obj)) {
            for (i = 0, len = obj.length; i < len; i++) iteratee(obj[i], i, obj);
        } else {
            var _keys = keys(obj);
            for (i = 0, len = _keys.length; i < len; i++) {
                iteratee(obj[_keys[i]], _keys[i], obj);
            }
        }

        return obj;
    }

    return exports;
})();

/* ------------------------------ createAssigner ------------------------------ */

export var createAssigner = _.createAssigner = (function () {
    /* Used to create extend, extendOwn and defaults.
     *
     * |Name    |Type    |Desc                          |
     * |--------|--------|------------------------------|
     * |keysFn  |function|Function to get object keys   |
     * |defaults|boolean |No override when set to true  |
     * |return  |function|Result function, extend...    |
     */

    /* module
     * env: all
     * test: all
     */

    /* dependencies
     * isUndef each 
     */

    function exports(keysFn, defaults) {
        return function(obj) {
            each(arguments, function(src, idx) {
                if (idx === 0) return;

                var keys = keysFn(src);

                each(keys, function(key) {
                    if (!defaults || isUndef(obj[key])) obj[key] = src[key];
                });
            });

            return obj;
        };
    }

    return exports;
})();

/* ------------------------------ extend ------------------------------ */

export var extend = _.extend = (function (exports) {
    /* Copy all of the properties in the source objects over to the destination object.
     *
     * |Name  |Type  |Desc              |
     * |------|------|------------------|
     * |obj   |object|Destination object|
     * |...src|object|Sources objects   |
     * |return|object|Destination object|
     *
     * ```javascript
     * extend({name: 'RedHood'}, {age: 24}); // -> {name: 'RedHood', age: 24}
     * ```
     */

    /* module
     * env: all
     * test: all
     */

    /* dependencies
     * createAssigner allKeys 
     */

    exports = createAssigner(allKeys);

    return exports;
})({});

/* ------------------------------ extendOwn ------------------------------ */

export var extendOwn = _.extendOwn = (function (exports) {
    /* Like extend, but only copies own properties over to the destination object.
     *
     * |Name  |Type  |Desc              |
     * |------|------|------------------|
     * |obj   |object|Destination object|
     * |*src  |object|Sources objects   |
     * |return|object|Destination object|
     *
     * ```javascript
     * extendOwn({name: 'RedHood'}, {age: 24}); // -> {name: 'RedHood', age: 24}
     * ```
     */

    /* module
     * env: all
     * test: all
     */

    /* dependencies
     * keys createAssigner 
     */

    exports = createAssigner(keys);

    return exports;
})({});

/* ------------------------------ isEmpty ------------------------------ */

export var isEmpty = _.isEmpty = (function () {
    /* Check if value is an empty object or array.
     *
     * |Name  |Type   |Desc                  |
     * |------|-------|----------------------|
     * |val   |*      |Value to check        |
     * |return|boolean|True if value is empty|
     *
     * ```javascript
     * isEmpty([]); // -> true
     * isEmpty({}); // -> true
     * isEmpty(''); // -> true
     * ```
     */

    /* module
     * env: all
     * test: all
     */

    /* dependencies
     * isArrLike isArr isStr isArgs keys 
     */

    function exports(val) {
        if (val == null) return true;

        if (isArrLike(val) && (isArr(val) || isStr(val) || isArgs(val))) {
            return val.length === 0;
        }

        return keys(val).length === 0;
    }

    return exports;
})();

/* ------------------------------ isEmail ------------------------------ */

export var isEmail = _.isEmail = (function () {
    /* Loosely validate an email address.
     *
     * |Name  |Type   |Desc                                 |
     * |------|-------|-------------------------------------|
     * |val   |string |Value to check                       |
     * |return|boolean|True if value is an email like string|
     *
     * ```javascript
     * isEmail('surunzi@foxmail.com'); // -> true
     * ```
     */

    /* module
     * env: all
     * test: all
     */

    function exports(val) {
        return regEmail.test(val);
    }

    var regEmail = /.+@.+\..+/;

    return exports;
})();

/* ------------------------------ isValid ------------------------------ */

export var isNameValid = _.isNameValid = (function () {
    /* Loosely validate a filename.
     *
     * |Name  |Type   |Desc                                 |
     * |------|-------|-------------------------------------|
     * |val   |string |Value to check                       |
     * |return|boolean|True if value is a filename like string|
     *
     * ```javascript
     * isNameValid('test'); // -> true
     * ```
     */

    /* module
     * env: all
     * test: all
     */

    function exports(val) {
        return !regName.test(val)
    }

    var regName = /[~!#$%^&*()=+|\\[\]{};':",?\/<>]+/

    return exports;
})();

/* ------------------------------ isMatch ------------------------------ */

export var isMatch = _.isMatch = (function () {
    /* Check if keys and values in src are contained in obj.
     *
     * |Name  |Type   |Desc                              |
     * |------|-------|----------------------------------|
     * |obj   |object |Object to inspect                 |
     * |src   |object |Object of property values to match|
     * |return|boolean|True if object is match           |
     *
     * ```javascript
     * isMatch({a: 1, b: 2}, {a: 1}); // -> true
     * ```
     */

    /* module
     * env: all
     * test: all
     */

    /* dependencies
     * keys 
     */

    function exports(obj, src) {
        var _keys = keys(src),
            len = _keys.length;

        if (obj == null) return !len;

        obj = Object(obj);

        for (var i = 0; i < len; i++) {
            var key = _keys[i];
            if (src[key] !== obj[key] || !(key in obj)) return false;
        }

        return true;
    }

    return exports;
})();

/* ------------------------------ repeat ------------------------------ */

export var repeat = _.repeat = (function (exports) {
    /* Repeat string n-times.
     *
     * |Name  |Type  |Desc            |
     * |------|------|----------------|
     * |str   |string|String to repeat|
     * |n     |number|Repeat times    |
     * |return|string|Repeated string |
     *
     * ```javascript
     * repeat('a', 3); // -> 'aaa'
     * repeat('ab', 2); // -> 'abab'
     * repeat('*', 0); // -> ''
     * ```
     */

    /* module
     * env: all
     * test: all
     */

    exports = function(str, n) {
        var ret = '';

        if (n < 1) return '';

        while (n > 0) {
            if (n & 1) ret += str;
            n >>= 1;
            str += str;
        }

        return ret;
    };

    return exports;
})({});

/* ------------------------------ lpad ------------------------------ */

export var lpad = _.lpad = (function () {
    /* Pad string on the left side if it's shorter than length.
     *
     * |Name   |Type  |Desc                  |
     * |-------|------|----------------------|
     * |str    |string|String to pad         |
     * |len    |number|Padding length        |
     * |[chars]|string|String used as padding|
     * |return |string|Resulted string       |
     *
     * ```javascript
     * lpad('a', 5); // -> '    a'
     * lpad('a', 5, '-'); // -> '----a'
     * lpad('abc', 3, '-'); // -> 'abc'
     * lpad('abc', 5, 'ab'); // -> 'ababc'
     * ```
     */

    /* module
     * env: all
     * test: all
     */

    /* dependencies
     * repeat toStr 
     */

    function exports(str, len, chars) {
        str = toStr(str);

        var strLen = str.length;

        chars = chars || ' ';

        if (strLen < len) str = (repeat(chars, len - strLen) + str).slice(-len);

        return str;
    }

    return exports;
})();

/* ------------------------------ dateFormat ------------------------------ */

export var dateFormat = _.dateFormat = (function () {
    /* Simple but extremely useful date format function.
     *
     * |Name           |Type   |Desc                 |
     * |---------------|-------|---------------------|
     * |[date=new Date]|Date   |Date object to format|
     * |mask           |string |Format mask          |
     * |[utc=false]    |boolean|UTC or not           |
     * |[gmt=false]    |boolean|GMT or not           |
     *
     * |Mask|Description                                                      |
     * |----|-----------------------------------------------------------------|
     * |d   |Day of the month as digits; no leading zero for single-digit days|
     * |dd  |Day of the month as digits; leading zero for single-digit days   |
     * |ddd |Day of the week as a three-letter abbreviation                   |
     * |dddd|Day of the week as its full name                                 |
     * |m   |Month as digits; no leading zero for single-digit months         |
     * |mm  |Month as digits; leading zero for single-digit months            |
     * |mmm |Month as a three-letter abbreviation                             |
     * |mmmm|Month as its full name                                           |
     * |yy  |Year as last two digits; leading zero for years less than 10     |
     * |yyyy|Year represented by four digits                                  |
     * |h   |Hours; no leading zero for single-digit hours (12-hour clock)    |
     * |hh  |Hours; leading zero for single-digit hours (12-hour clock)       |
     * |H   |Hours; no leading zero for single-digit hours (24-hour clock)    |
     * |HH  |Hours; leading zero for single-digit hours (24-hour clock)       |
     * |M   |Minutes; no leading zero for single-digit minutes                |
     * |MM  |Minutes; leading zero for single-digit minutes                   |
     * |s   |Seconds; no leading zero for single-digit seconds                |
     * |ss  |Seconds; leading zero for single-digit seconds                   |
     * |l L |Milliseconds. l gives 3 digits. L gives 2 digits                 |
     * |t   |Lowercase, single-character time marker string: a or p           |
     * |tt  |Lowercase, two-character time marker string: am or pm            |
     * |T   |Uppercase, single-character time marker string: A or P           |
     * |TT  |Uppercase, two-character time marker string: AM or PM            |
     * |Z   |US timezone abbreviation, e.g. EST or MDT                        |
     * |o   |GMT/UTC timezone offset, e.g. -0500 or +0230                     |
     * |S   |The date's ordinal suffix (st, nd, rd, or th)                    |
     * |UTC:|Must be the first four characters of the mask                    |
     *
     * ```javascript
     * dateFormat('isoDate'); // -> 2016-11-19
     * dateFormat('yyyy-mm-dd HH:MM:ss'); // -> 2016-11-19 19:00:04
     * dateFormat(new Date(), 'yyyy-mm-dd'); // -> 2016-11-19
     * ```
     */

    /* module
     * env: all
     * test: all
     */

    /* dependencies
     * isStr isDate toStr lpad 
     */

    function exports(date, mask, utc, gmt) {
        if (arguments.length === 1 && isStr(date) && !regNum.test(date)) {
            mask = date;
            date = undefined;
        }

        date = date || new Date();

        if (!isDate(date)) date = new Date(date);

        mask = toStr(exports.masks[mask] || mask || exports.masks['default']);

        var maskSlice = mask.slice(0, 4);

        if (maskSlice === 'UTC:' || maskSlice === 'GMT:') {
            mask = mask.slice(4);
            utc = true;
            if (maskSlice === 'GMT:') gmt = true;
        }

        var prefix = utc ? 'getUTC' : 'get',
            d = date[prefix + 'Date'](),
            D = date[prefix + 'Day'](),
            m = date[prefix + 'Month'](),
            y = date[prefix + 'FullYear'](),
            H = date[prefix + 'Hours'](),
            M = date[prefix + 'Minutes'](),
            s = date[prefix + 'Seconds'](),
            L = date[prefix + 'Milliseconds'](),
            o = utc ? 0 : date.getTimezoneOffset(),
            flags = {
                d: d,
                dd: padZero(d),
                ddd: exports.i18n.dayNames[D],
                dddd: exports.i18n.dayNames[D + 7],
                m: m + 1,
                mm: padZero(m + 1),
                mmm: exports.i18n.monthNames[m],
                mmmm: exports.i18n.monthNames[m + 12],
                yy: toStr(y).slice(2),
                yyyy: y,
                h: H % 12 || 12,
                hh: padZero(H % 12 || 12),
                H: H,
                HH: padZero(H),
                M: M,
                MM: padZero(M),
                s: s,
                ss: padZero(s),
                l: padZero(L, 3),
                L: padZero(Math.round(L / 10)),
                t: H < 12 ? 'a' : 'p',
                tt: H < 12 ? 'am' : 'pm',
                T: H < 12 ? 'A' : 'P',
                TT: H < 12 ? 'AM' : 'PM',
                Z: gmt
                    ? 'GMT'
                    : utc
                        ? 'UTC'
                        : (toStr(date).match(regTimezone) || [''])
                              .pop()
                              .replace(regTimezoneClip, ''),
                o:
                    (o > 0 ? '-' : '+') +
                    padZero(
                        Math.floor(Math.abs(o) / 60) * 100 + (Math.abs(o) % 60),
                        4
                    ),
                S: ['th', 'st', 'nd', 'rd'][
                    d % 10 > 3 ? 0 : (((d % 100) - (d % 10) != 10) * d) % 10
                ]
            };

        return mask.replace(regToken, function(match) {
            if (match in flags) return flags[match];

            return match.slice(1, match.length - 1);
        });
    }

    function padZero(str, len) {
        return lpad(toStr(str), len || 2, '0');
    }

    var regToken = /d{1,4}|m{1,4}|yy(?:yy)?|([HhMsTt])\1?|[LloSZWN]|'[^']*'|'[^']*'/g,
        regTimezone = /\b(?:[PMCEA][SDP]T|(?:Pacific|Mountain|Central|Eastern|Atlantic) (?:Standard|Daylight|Prevailing) Time|(?:GMT|UTC)(?:[-+]\d{4})?)\b/g,
        regNum = /\d/,
        regTimezoneClip = /[^-+\dA-Z]/g;

    exports.masks = {
        default: 'ddd mmm dd yyyy HH:MM:ss',
        shortDate: 'm/d/yy',
        mediumDate: 'mmm d, yyyy',
        longDate: 'mmmm d, yyyy',
        fullDate: 'dddd, mmmm d, yyyy',
        shortTime: 'h:MM TT',
        mediumTime: 'h:MM:ss TT',
        longTime: 'h:MM:ss TT Z',
        isoDate: 'yyyy-mm-dd',
        isoTime: 'HH:MM:ss',
        isoDateTime: "yyyy-mm-dd'T'HH:MM:sso",
        isoUtcDateTime: "UTC:yyyy-mm-dd'T'HH:MM:ss'Z'",
        expiresHeaderFormat: 'ddd, dd mmm yyyy HH:MM:ss Z'
    };

    exports.i18n = {
        dayNames: [
            'Sun',
            'Mon',
            'Tue',
            'Wed',
            'Thu',
            'Fri',
            'Sat',
            'Sunday',
            'Monday',
            'Tuesday',
            'Wednesday',
            'Thursday',
            'Friday',
            'Saturday'
        ],
        monthNames: [
            'Jan',
            'Feb',
            'Mar',
            'Apr',
            'May',
            'Jun',
            'Jul',
            'Aug',
            'Sep',
            'Oct',
            'Nov',
            'Dec',
            'January',
            'February',
            'March',
            'April',
            'May',
            'June',
            'July',
            'August',
            'September',
            'October',
            'November',
            'December'
        ]
    };

    return exports;
})();

/* ------------------------------ ltrim ------------------------------ */

export var ltrim = _.ltrim = (function () {
    /* Remove chars or white-spaces from beginning of string.
     *
     * |Name  |Type        |Desc              |
     * |------|------------|------------------|
     * |str   |string      |String to trim    |
     * |chars |string array|Characters to trim|
     * |return|string      |Trimmed string    |
     *
     * ```javascript
     * ltrim(' abc  '); // -> 'abc  '
     * ltrim('_abc_', '_'); // -> 'abc_'
     * ltrim('_abc_', ['a', '_']); // -> 'bc_'
     * ```
     */

    /* module
     * env: all
     * test: all
     */

    var regSpace = /^\s+/;

    function exports(str, chars) {
        if (chars == null) return str.replace(regSpace, '');

        var start = 0,
            len = str.length,
            charLen = chars.length,
            found = true,
            i,
            c;

        while (found && start < len) {
            found = false;
            i = -1;
            c = str.charAt(start);

            while (++i < charLen) {
                if (c === chars[i]) {
                    found = true;
                    start++;
                    break;
                }
            }
        }

        return start >= len ? '' : str.substr(start, len);
    }

    return exports;
})();

/* ------------------------------ matcher ------------------------------ */

export var matcher = _.matcher = (function () {
    /* Return a predicate function that checks if attrs are contained in an object.
     *
     * |Name  |Type    |Desc                              |
     * |------|--------|----------------------------------|
     * |attrs |object  |Object of property values to match|
     * |return|function|New predicate function            |
     *
     * ```javascript
     * var objects = [
     *     {a: 1, b: 2, c: 3 },
     *     {a: 4, b: 5, c: 6 }
     * ];
     * filter(objects, matcher({a: 4, c: 6 })); // -> [{a: 4, b: 5, c: 6 }]
     * ```
     */

    /* module
     * env: all
     * test: all
     */

    /* dependencies
     * extendOwn isMatch 
     */

    function exports(attrs) {
        attrs = extendOwn({}, attrs);

        return function(obj) {
            return isMatch(obj, attrs);
        };
    }

    return exports;
})();

/* ------------------------------ safeCb ------------------------------ */

export var safeCb = _.safeCb = (function (exports) {
    /* Create callback based on input value.
     */

    /* module
     * env: all
     * test: all
     */

    /* dependencies
     * isFn isObj optimizeCb matcher identity 
     */

    exports = function(val, ctx, argCount) {
        if (val == null) return identity;

        if (isFn(val)) return optimizeCb(val, ctx, argCount);

        if (isObj(val)) return matcher(val);

        return function(key) {
            return function(obj) {
                return obj == null ? undefined : obj[key];
            };
        };
    };

    return exports;
})({});

/* ------------------------------ filter ------------------------------ */

export var filter = _.filter = (function () {
    /* Iterates over elements of collection, returning an array of all the values that pass a truth test.
     *
     * |Name     |Type    |Desc                                   |
     * |---------|--------|---------------------------------------|
     * |obj      |array   |Collection to iterate over             |
     * |predicate|function|Function invoked per iteration         |
     * |[ctx]    |*       |Predicate context                      |
     * |return   |array   |Array of all values that pass predicate|
     *
     * ```javascript
     * filter([1, 2, 3, 4, 5], function (val)
     * {
     *     return val % 2 === 0;
     * }); // -> [2, 4]
     * ```
     */

    /* module
     * env: all
     * test: all
     */

    /* dependencies
     * safeCb each 
     */

    function exports(obj, predicate, ctx) {
        var ret = [];

        predicate = safeCb(predicate, ctx);

        each(obj, function(val, idx, list) {
            if (predicate(val, idx, list)) ret.push(val);
        });

        return ret;
    }

    return exports;
})();

/* ------------------------------ map ------------------------------ */

export var map = _.map = (function () {
    /* Create an array of values by running each element in collection through iteratee.
     *
     * |Name    |Type        |Desc                          |
     * |--------|------------|------------------------------|
     * |obj     |array object|Collection to iterate over    |
     * |iteratee|function    |Function invoked per iteration|
     * |[ctx]   |*           |Function context              |
     * |return  |array       |New mapped array              |
     *
     * ```javascript
     * map([4, 8], function (n) { return n * n; }); // -> [16, 64]
     * ```
     */

    /* module
     * env: all
     * test: all
     */

    /* dependencies
     * safeCb keys isArrLike 
     */

    function exports(obj, iteratee, ctx) {
        iteratee = safeCb(iteratee, ctx);

        var _keys = !isArrLike(obj) && keys(obj),
            len = (_keys || obj).length,
            results = Array(len);

        for (var i = 0; i < len; i++) {
            var curKey = _keys ? _keys[i] : i;
            results[i] = iteratee(obj[curKey], curKey, obj);
        }

        return results;
    }

    return exports;
})();

/* ------------------------------ toArr ------------------------------ */

export var toArr = _.toArr = (function () {
    /* Convert value to an array.
     *
     * |Name  |Type |Desc            |
     * |------|-----|----------------|
     * |val   |*    |Value to convert|
     * |return|array|Converted array |
     *
     * ```javascript
     * toArr({a: 1, b: 2}); // -> [{a: 1, b: 2}]
     * toArr('abc'); // -> ['abc']
     * toArr(1); // -> [1]
     * toArr(null); // -> []
     * ```
     */

    /* module
     * env: all
     * test: all
     */

    /* dependencies
     * isArrLike map isArr isStr 
     */

    function exports(val) {
        if (!val) return [];

        if (isArr(val)) return val;

        if (isArrLike(val) && !isStr(val)) return map(val);

        return [val];
    }

    return exports;
})();

/* ------------------------------ Class ------------------------------ */

export var Class = _.Class = (function () {
    /* Create JavaScript class.
     *
     * |Name     |Type    |Desc                             |
     * |---------|--------|---------------------------------|
     * |methods  |object  |Public methods                   |
     * |[statics]|object  |Static methods                   |
     * |return   |function|Function used to create instances|
     *
     * ```javascript
     * var People = Class({
     *     initialize: function People(name, age)
     *     {
     *         this.name = name;
     *         this.age = age;
     *     },
     *     introduce: function ()
     *     {
     *         return 'I am ' + this.name + ', ' + this.age + ' years old.';
     *     }
     * });
     *
     * var Student = People.extend({
     *     initialize: function Student(name, age, school)
     *     {
     *         this.callSuper(People, 'initialize', arguments);
     *
     *         this.school = school;
     *     },
     *     introduce: function ()
     *     {
     *         return this.callSuper(People, 'introduce') + '\n I study at ' + this.school + '.';
     *     }
     * }, {
     *     is: function (obj)
     *     {
     *         return obj instanceof Student;
     *     }
     * });
     *
     * var a = new Student('allen', 17, 'Hogwarts');
     * a.introduce(); // -> 'I am allen, 17 years old. \n I study at Hogwarts.'
     * Student.is(a); // -> true
     * ```
     */

    /* module
     * env: all
     * test: all
     */

    /* dependencies
     * extend toArr inherits safeGet isMiniProgram 
     */

    function exports(methods, statics) {
        return Base.extend(methods, statics);
    }

    function makeClass(parent, methods, statics) {
        statics = statics || {};
        var className =
            methods.className || safeGet(methods, 'initialize.name') || '';
        delete methods.className;

        var ctor;
        if (isMiniProgram) {
            ctor = function() {
                var args = toArr(arguments);
                return this.initialize
                    ? this.initialize.apply(this, args) || this
                    : this;
            };
        } else {
            ctor = new Function(
                'toArr',
                'return function ' +
                    className +
                    '()' +
                    '{' +
                    'var args = toArr(arguments);' +
                    'return this.initialize ? this.initialize.apply(this, args) || this : this;' +
                    '};'
            )(toArr);
        }

        inherits(ctor, parent);
        ctor.prototype.constructor = ctor;

        ctor.extend = function(methods, statics) {
            return makeClass(ctor, methods, statics);
        };
        ctor.inherits = function(Class) {
            inherits(ctor, Class);
        };
        ctor.methods = function(methods) {
            extend(ctor.prototype, methods);
            return ctor;
        };
        ctor.statics = function(statics) {
            extend(ctor, statics);
            return ctor;
        };

        ctor.methods(methods).statics(statics);

        return ctor;
    }

    var Base = (exports.Base = makeClass(Object, {
        className: 'Base',
        callSuper: function(parent, name, args) {
            var superMethod = parent.prototype[name];

            return superMethod.apply(this, args);
        },
        toString: function() {
            return this.constructor.name;
        }
    }));

    return exports;
})();

/* ------------------------------ mapObj ------------------------------ */

export var mapObj = _.mapObj = (function () {
    /* Map for objects.
     *
     * |Name    |Type    |Desc                          |
     * |--------|--------|------------------------------|
     * |obj     |object  |Object to iterate over        |
     * |iteratee|function|Function invoked per iteration|
     * |[ctx]   |*       |Function context              |
     * |return  |object  |New mapped object             |
     *
     * ```javascript
     * mapObj({a: 1, b: 2}, function (val, key) { return val + 1 }); // -> {a: 2, b: 3}
     * ```
     */

    /* module
     * env: all
     * test: all
     */

    /* dependencies
     * safeCb keys 
     */

    function exports(obj, iteratee, ctx) {
        iteratee = safeCb(iteratee, ctx);

        var _keys = keys(obj),
            len = _keys.length,
            ret = {};

        for (var i = 0; i < len; i++) {
            var curKey = _keys[i];
            ret[curKey] = iteratee(obj[curKey], curKey, obj);
        }

        return ret;
    }

    return exports;
})();

/* ------------------------------ cloneDeep ------------------------------ */

export var cloneDeep = _.cloneDeep = (function () {
    /* Recursively clone value.
     *
     * |Name  |Type|Desc             |
     * |------|----|-----------------|
     * |val   |*   |Value to clone   |
     * |return|*   |Deep cloned Value|
     *
     * ```javascript
     * var obj = [{a: 1}, {a: 2}];
     * var obj2 = cloneDeep(obj);
     * console.log(obj[0] === obj2[1]); // -> false
     * ```
     */

    /* module
     * env: all
     * test: all
     */

    /* dependencies
     * isObj isFn isArr mapObj 
     */

    function exports(obj) {
        if (isArr(obj)) {
            return obj.map(function(val) {
                return exports(val);
            });
        }

        if (isObj(obj) && !isFn(obj)) {
            return mapObj(obj, function(val) {
                return exports(val);
            });
        }

        return obj;
    }

    return exports;
})();

/* ------------------------------ extendDeep ------------------------------ */

export var extendDeep = _.extendDeep = (function () {
    /* Recursive object extending.
     *
     * |Name  |Type  |Desc              |
     * |------|------|------------------|
     * |obj   |object|Destination object|
     * |...src|object|Sources objects   |
     * |return|object|Destination object|
     *
     * ```javascript
     * extendDeep({
     *     name: 'RedHood',
     *     family: {
     *         mother: 'Jane',
     *         father: 'Jack'
     *     }
     * }, {
     *     family: {
     *         brother: 'Bruce'
     *     }
     * });
     * // -> {name: 'RedHood', family: {mother: 'Jane', father: 'Jack', brother: 'Bruce'}}
     * ```
     */

    /* module
     * env: all
     * test: all
     */

    /* dependencies
     * isPlainObj each cloneDeep 
     */

    function exports(obj) {
        var i = 0,
            ret = obj,
            len = arguments.length;

        while (++i < len) {
            obj = arguments[i];

            if (isPlainObj(ret) && isPlainObj(obj)) {
                each(obj, function(val, key) {
                    ret[key] = exports(ret[key], obj[key]);
                });
            } else {
                ret = cloneDeep(obj);
            }
        }

        return ret;
    }

    return exports;
})();

/* ------------------------------ rtrim ------------------------------ */

export var rtrim = _.rtrim = (function () {
    /* Remove chars or white-spaces from end of string.
     *
     * |Name  |Type        |Desc              |
     * |------|------------|------------------|
     * |str   |string      |String to trim    |
     * |chars |string array|Characters to trim|
     * |return|string      |Trimmed string    |
     *
     * ```javascript
     * rtrim(' abc  '); // -> ' abc'
     * rtrim('_abc_', '_'); // -> '_abc'
     * rtrim('_abc_', ['c', '_']); // -> '_ab'
     * ```
     */

    /* module
     * env: all
     * test: all
     */

    var regSpace = /\s+$/;

    function exports(str, chars) {
        if (chars == null) return str.replace(regSpace, '');

        var end = str.length - 1,
            charLen = chars.length,
            found = true,
            i,
            c;

        while (found && end >= 0) {
            found = false;
            i = -1;
            c = str.charAt(end);

            while (++i < charLen) {
                if (c === chars[i]) {
                    found = true;
                    end--;
                    break;
                }
            }
        }

        return end >= 0 ? str.substring(0, end + 1) : '';
    }

    return exports;
})();

/* ------------------------------ trim ------------------------------ */

export var trim = _.trim = (function () {
    /* Remove chars or white-spaces from beginning end of string.
     *
     * |Name  |Type        |Desc              |
     * |------|------------|------------------|
     * |str   |string      |String to trim    |
     * |chars |string array|Characters to trim|
     * |return|string      |Trimmed string    |
     *
     * ```javascript
     * trim(' abc  '); // -> 'abc'
     * trim('_abc_', '_'); // -> 'abc'
     * trim('_abc_', ['a', 'c', '_']); // -> 'b'
     * ```
     */

    /* module
     * env: all
     * test: all
     */

    /* dependencies
     * ltrim rtrim 
     */

    var regSpace = /^\s+|\s+$/g;

    function exports(str, chars) {
        if (chars == null) return str.replace(regSpace, '');

        return ltrim(rtrim(str, chars), chars);
    }

    return exports;
})();

/* ------------------------------ query ------------------------------ */

export var query = _.query = (function (exports) {
    /* Parse and stringify url query strings.
     *
     * ### parse
     *
     * Parse a query string into an object.
     *
     * |Name  |Type  |Desc        |
     * |------|------|------------|
     * |str   |string|Query string|
     * |return|object|Query object|
     *
     * ### stringify
     *
     * Stringify an object into a query string.
     *
     * |Name  |Type  |Desc        |
     * |------|------|------------|
     * |obj   |object|Query object|
     * |return|string|Query string|
     *
     * ```javascript
     * query.parse('foo=bar&eruda=true'); // -> {foo: 'bar', eruda: 'true'}
     * query.stringify({foo: 'bar', eruda: 'true'}); // -> 'foo=bar&eruda=true'
     * query.parse('name=eruda&name=eustia'); // -> {name: ['eruda', 'eustia']}
     * ```
     */

    /* module
     * env: all
     * test: all
     */

    /* dependencies
     * trim each isUndef isArr map isEmpty filter isObj 
     */

    exports = {
        parse: function(str) {
            var ret = {};

            str = trim(str).replace(regIllegalChars, '');

            each(str.split('&'), function(param) {
                var parts = param.split('=');

                var key = parts.shift(),
                    val = parts.length > 0 ? parts.join('=') : null;

                key = decodeURIComponent(key);
                val = decodeURIComponent(val);

                if (isUndef(ret[key])) {
                    ret[key] = val;
                } else if (isArr(ret[key])) {
                    ret[key].push(val);
                } else {
                    ret[key] = [ret[key], val];
                }
            });

            return ret;
        },
        stringify: function(obj, arrKey) {
            return filter(
                map(obj, function(val, key) {
                    if (isObj(val) && isEmpty(val)) return '';
                    if (isArr(val)) return exports.stringify(val, key);

                    return (
                        (arrKey
                            ? encodeURIComponent(arrKey)
                            : encodeURIComponent(key)) +
                        '=' +
                        encodeURIComponent(val)
                    );
                }),
                function(str) {
                    return str.length > 0;
                }
            ).join('&');
        }
    };

    var regIllegalChars = /^(\?|#|&)/g;

    return exports;
})({});

/* ------------------------------ Url ------------------------------ */

export var Url = _.Url = (function (exports) {
    /* Simple url manipulator.
     *
     * ### constructor
     *
     * |Name        |Type  |Desc      |
     * |------------|------|----------|
     * |url=location|string|Url string|
     *
     * ### setQuery
     *
     * Set query value.
     *
     * |Name  |Type  |Desc       |
     * |------|------|-----------|
     * |name  |string|Query name |
     * |value |string|Query value|
     * |return|Url   |this       |
     *
     * |Name  |Type  |Desc        |
     * |------|------|------------|
     * |names |object|query object|
     * |return|Url   |this        |
     *
     * ### rmQuery
     *
     * Remove query value.
     *
     * |Name  |Type        |Desc      |
     * |------|------------|----------|
     * |name  |string array|Query name|
     * |return|Url         |this      |
     *
     * ### parse
     *
     * [static] Parse url into an object.
     *
     * |Name  |Type  |Desc      |
     * |------|------|----------|
     * |url   |string|Url string|
     * |return|object|Url object|
     *
     * ### stringify
     *
     * [static] Stringify url object into a string.
     *
     * |Name  |Type  |Desc      |
     * |------|------|----------|
     * |url   |object|Url object|
     * |return|string|Url string|
     *
     * An url object contains the following properties:
     *
     * |Name    |Desc                                                                                  |
     * |--------|--------------------------------------------------------------------------------------|
     * |protocol|The protocol scheme of the URL (e.g. http:)                                           |
     * |slashes |A boolean which indicates whether the protocol is followed by two forward slashes (//)|
     * |auth    |Authentication information portion (e.g. username:password)                           |
     * |hostname|Host name without port number                                                         |
     * |port    |Optional port number                                                                  |
     * |pathname|URL path                                                                              |
     * |query   |Parsed object containing query string                                                 |
     * |hash    |The "fragment" portion of the URL including the pound-sign (#)                        |
     *
     * ```javascript
     * var url = new Url('http://example.com:8080?eruda=true');
     * console.log(url.port); // -> '8080'
     * url.query.foo = 'bar';
     * url.rmQuery('eruda');
     * utl.toString(); // -> 'http://example.com:8080/?foo=bar'
     * ```
     */

    /* module
     * env: all
     * test: all
     */

    /* dependencies
     * Class extend trim query isEmpty each isArr toArr isBrowser 
     */

    exports = Class(
        {
            className: 'Url',
            initialize: function(url) {
                if (!url && isBrowser) url = window.location.href;
                extend(this, exports.parse(url || ''));
            },
            setQuery: function(name, val) {
                var query = this.query;

                if (isObj(name)) {
                    each(name, function(val, key) {
                        query[key] = val;
                    });
                } else {
                    query[name] = val;
                }

                return this;
            },
            rmQuery: function(name) {
                var query = this.query;

                if (!isArr(name)) name = toArr(name);
                each(name, function(key) {
                    delete query[key];
                });

                return this;
            },
            toString: function() {
                return exports.stringify(this);
            }
        },
        {
            parse: function(url) {
                var ret = {
                        protocol: '',
                        auth: '',
                        hostname: '',
                        hash: '',
                        query: {},
                        port: '',
                        pathname: '',
                        slashes: false
                    },
                    rest = trim(url);

                var proto = rest.match(regProto);
                if (proto) {
                    proto = proto[0];
                    ret.protocol = proto.toLowerCase();
                    rest = rest.substr(proto.length);
                }

                if (proto) {
                    var slashes = rest.substr(0, 2) === '//';
                    if (slashes) {
                        rest = rest.slice(2);
                        ret.slashes = true;
                    }
                }

                if (slashes) {
                    var hostEnd = -1;
                    for (var i = 0, len = hostEndingChars.length; i < len; i++) {
                        var pos = rest.indexOf(hostEndingChars[i]);
                        if (pos !== -1 && (hostEnd === -1 || pos < hostEnd))
                            hostEnd = pos;
                    }

                    var host = rest.slice(0, hostEnd);
                    rest = rest.slice(hostEnd);

                    var atSign = host.lastIndexOf('@');

                    if (atSign !== -1) {
                        ret.auth = decodeURIComponent(host.slice(0, atSign));
                        host = host.slice(atSign + 1);
                    }

                    ret.hostname = host;
                    var port = host.match(regPort);
                    if (port) {
                        port = port[0];
                        if (port !== ':') ret.port = port.substr(1);
                        ret.hostname = host.substr(0, host.length - port.length);
                    }
                }

                var hash = rest.indexOf('#');

                if (hash !== -1) {
                    ret.hash = rest.substr(hash);
                    rest = rest.slice(0, hash);
                }

                var queryMark = rest.indexOf('?');

                if (queryMark !== -1) {
                    ret.query = query.parse(rest.substr(queryMark + 1));
                    rest = rest.slice(0, queryMark);
                }

                ret.pathname = rest || '/';

                return ret;
            },
            stringify: function(obj) {
                var ret =
                    obj.protocol +
                    (obj.slashes ? '//' : '') +
                    (obj.auth ? encodeURIComponent(obj.auth) + '@' : '') +
                    obj.hostname +
                    (obj.port ? ':' + obj.port : '') +
                    obj.pathname;

                if (!isEmpty(obj.query)) ret += '?' + query.stringify(obj.query);
                if (obj.hash) ret += obj.hash;

                return ret;
            }
        }
    );

    var regProto = /^([a-z0-9.+-]+:)/i,
        regPort = /:[0-9]*$/,
        hostEndingChars = ['/', '?', '#'];

    return exports;
})({});

/* ------------------------------ getUrlParam ------------------------------ */

export var getUrlParam = _.getUrlParam = (function () {
    /* Get url param.
     *
     * |Name        |Type  |Desc            |
     * |------------|------|----------------|
     * |name        |string|Param name      |
     * |url=location|string|Url to get param|
     * |return      |string|Param value     |
     * 
     * ```javascript
     * getUrlParam('test', 'http://example.com/?test=true'); // -> 'true'
     * ```
     */

    /* module
     * env: all
     * test: all
     */

    /* dependencies
     * Url 
     */

    function exports(name, url) {
        return new Url(url).query[name];
    }

    return exports;
})();

/* ------------------------------ toNum ------------------------------ */

export var toNum = _.toNum = (function (exports) {
    /* Convert value to a number.
     *
     * |Name  |Type  |Desc            |
     * |------|------|----------------|
     * |val   |*     |Value to process|
     * |return|number|Resulted number |
     *
     * ```javascript
     * toNum('5'); // -> 5
     * ```
     */

    /* module
     * env: all
     * test: all
     */

    /* dependencies
     * isNum isObj isFn isStr 
     */

    exports = function(val) {
        if (isNum(val)) return val;

        if (isObj(val)) {
            var temp = isFn(val.valueOf) ? val.valueOf() : val;
            val = isObj(temp) ? temp + '' : temp;
        }

        if (!isStr(val)) return val === 0 ? val : +val;

        return +val;
    };

    return exports;
})({});

/* ------------------------------ toInt ------------------------------ */

export var toInt = _.toInt = (function () {
    /* Convert value to an integer.
     *
     * |Name  |Type  |Desc             |
     * |------|------|-----------------|
     * |val   |*     |Value to convert |
     * |return|number|Converted integer|
     *
     * ```javascript
     * toInt(1.1); // -> 1
     * toInt(undefined); // -> 0
     * ```
     */

    /* module
     * env: all
     * test: all
     */

    /* dependencies
     * toNum 
     */

    function exports(val) {
        if (!val) return val === 0 ? val : 0;

        val = toNum(val);

        return val - (val % 1);
    }

    return exports;
})();

/* ------------------------------ detectBrowser ------------------------------ */

export var detectBrowser = _.detectBrowser = (function () {
    /* Detect browser info using ua.
     *
     * |Name                    |Type  |Desc                              |
     * |------------------------|------|----------------------------------|
     * |[ua=navigator.userAgent]|string|Browser userAgent                 |
     * |return                  |object|Object containing name and version|
     * 
     * Browsers supported: ie, chrome, edge, firefox, opera, safari, ios(mobile safari), android(android browser)
     *
     * ```javascript
     * var browser = detectBrowser();
     * if (browser.name === 'ie' && browser.version < 9) 
     * {
     *     // Do something about old IE...
     * }
     * ```
     */

    /* module
     * env: all
     * test: all
     */

    /* dependencies
     * isBrowser toInt keys 
     */

    function exports(ua) {
        ua = ua || (isBrowser ? navigator.userAgent : '');
        ua = ua.toLowerCase();

        var ieVer = getVer(ua, 'msie ');

        if (ieVer)
            return {
                version: ieVer,
                name: 'ie'
            };

        if (regIe11.test(ua))
            return {
                version: 11,
                name: 'ie'
            };

        for (var i = 0, len = browsers.length; i < len; i++) {
            var name = browsers[i],
                match = ua.match(regBrowsers[name]);

            if (match == null) continue;

            var version = toInt(match[1].split('.')[0]);

            if (name === 'opera') version = getVer(ua, 'version/') || version;

            return {
                name: name,
                version: version
            };
        }

        return {
            name: 'unknown',
            version: -1
        };
    }

    var regBrowsers = {
        edge: /edge\/([0-9._]+)/,
        firefox: /firefox\/([0-9.]+)(?:\s|$)/,
        opera: /opera\/([0-9.]+)(?:\s|$)/,
        android: /android\s([0-9.]+)/,
        ios: /version\/([0-9._]+).*mobile.*safari.*/,
        safari: /version\/([0-9._]+).*safari/,
        chrome: /(?!chrom.*opr)chrom(?:e|ium)\/([0-9.]+)(:?\s|$)/
    };

    var regIe11 = /trident\/7\./,
        browsers = keys(regBrowsers);

    function getVer(ua, mark) {
        var idx = ua.indexOf(mark);

        if (idx > -1)
            return toInt(ua.substring(idx + mark.length, ua.indexOf('.', idx)));
    }

    return exports;
})();

export default _;