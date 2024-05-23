<template>
  <div class="home">
    <h1>欢迎来到学生游学系统！</h1>
    <h2>——张晨阳、廖轩毅、徐路</h2>
    <!--添加注册按钮-->
    <router-link to="/register">
      <button>注册</button>
    </router-link>
    <!-- 直接提供登录按钮 -->
    <router-link to="/login">
      <button>登录</button>
    </router-link>
  </div>
</template>

<script>
export default {
  name: 'myHome',
};
</script>