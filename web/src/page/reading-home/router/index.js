import Vue from 'vue'
import VueRouter from 'vue-router'
import Test from '../components/test/Test.vue'
import Test2 from '../components/test/Test2.vue'


Vue.use(VueRouter)

export default new VueRouter({
    routes: [
        {
            path: '/',
            component: Test
        },
        {
            path: '/test2',
            component: Test2
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
