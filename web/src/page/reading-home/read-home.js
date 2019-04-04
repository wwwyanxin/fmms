import  Vue from 'vue'
import App from './App.vue'
import router from './router/index'
import ElementUI from 'element-ui';
import 'element-ui/lib/theme-chalk/index.css';
import global from '@/service/global'
import VueLazyLoad from 'vue-lazyload'


Vue.use(VueLazyLoad)
Vue.use(ElementUI);


// 全局eventbus
const EventBus = new Vue()
Vue.prototype.$bus = EventBus



const root = document.createElement('div');
document.body.appendChild(root);
const app = new Vue({
    render:(h)=>h(App),
    router
}).$mount(root)


global.set('app', app)
