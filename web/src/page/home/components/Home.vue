<template>
    <div>
        <img class="img">
        <el-row style="text-align: center;">
            <el-button @click="getTest" type="success">GET测试</el-button>
            <el-button @click="postTest" type="primary">POST测试</el-button>
        </el-row>
        <h1>{{textTest}}</h1>
    </div>
</template>

<script>
    import {cloneDeep,getUrl} from '@/lib/util'
    import Api from '@/service/api.js'

    export default {
        name: "Home",
        data(){
            return {
                textTest : "",
            }
        },
        created() {},
        beforeDestroy() {},
        async mounted(){

        },
        methods:{
            async getTest(){
                const res = await Api.get('course_order_list', {
                    // member_id:14
                });
                this.textTest = res;
                console.log(res);
            },
            async postTest(){
                const res = await Api.post('member_register', {
                    account:'test1',
                    password:'password1',
                    name:'name1',
                    sex:'male',
                })
                this.textTest = res;
                console.log(res);
            }
        },
        computed:{

        }
    }
</script>

<style scoped>
    div{
        background: pink;
        color:olivedrab;
    }

    .img{
        transform:rotate(17deg);
        background-image: url(../../../style/images/game.png);
        width:46px;
        height:45px;
    }

</style>
