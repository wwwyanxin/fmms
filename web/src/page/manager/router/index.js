import Vue from 'vue'
import VueRouter from 'vue-router'
import Login from '../components/Login'
// import Member from '../components/Member'


Vue.use(VueRouter)

export default new VueRouter({
    routes: [
        {
            path: '/',
            component: (resolve) => {
                require(['../components/Manager'], resolve)  //路由懒加载
            }
        },
        {
            path: '/login',
            component: Login
        }
        /* {
             path: '/',
             component: Today
         },
         {
             path: '/list/:folderId',
             component: MailList,
             props: true
         },
         {
             path: '/',
             component: Today
         },
         {
             path: '/container',
             component: container,
             children: [
                 {
                     path: 'bindwx',
                     component: Bindwx,
                     children: [
                         {
                             path: '',
                             component: stepHeader,
                             props: {
                                 content: ['注册账号', '注册完成']
                             }
                         }
                     ]
                 },
                 {
                     path: 'login_qq',
                     component: LoginQQ
                 }
             ]
         },
         {
             path: '/registersuccess',
             component: registersuccess,
             children: [
                 {
                     path: '',
                     component: registerAD
                 }
             ]
         }*/
    ]
})
