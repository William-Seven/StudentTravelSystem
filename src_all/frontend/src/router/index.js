//router/index.js
import { createRouter, createWebHistory } from 'vue-router';
import Home from '../views/myHome.vue';
import Login from '../components/myLogin.vue';
import Register from '../components/myRegister.vue';
import ForgotPassword from '../components/myForgotPassword.vue';
import ChangePassword from '../components/myChangePassword.vue';
import Dashboard from '../components/myDashboard.vue';

const routes = [
    { path: '/', component: Home },
    { path: '/login', component: Login },
    { path: '/register', component: Register },
    { path: '/forgot-password', component: ForgotPassword },
    { path: '/change-password', component: ChangePassword },
    { path: '/dashboard', component: Dashboard },
];

const router = createRouter({
    history: createWebHistory(process.env.BASE_URL),
    routes,
});

export default router;