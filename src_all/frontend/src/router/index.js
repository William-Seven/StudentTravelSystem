//router/index.js
import { createRouter, createWebHistory } from 'vue-router';
import Home from '../views/myHome.vue';
import Login from '../components/myLogin.vue';
import Register from '../components/myRegister.vue';
import ForgotPassword from '../components/myForgotPassword.vue';
import ChangePassword from '../components/myChangePassword.vue';
import Dashboard from '../components/myDashboard.vue';
import RoutePlanner from '../components/RoutePlanner.vue';
import StudyTourRecommendations from '../components/StudyTourRecommendations.vue';
import Description from '../components/myDescription.vue';
import PlaceQuery from '../components/PlaceQuery.vue';

const routes = [
    { path: '/', component: Home },
    { path: '/login', component: Login },
    { path: '/register', component: Register },
    { path: '/forgot-password', component: ForgotPassword },
    { path: '/change-password', component: ChangePassword },
    { path: '/dashboard', component: Dashboard },
    { path: '/route-planning', component: RoutePlanner },
    { path: '/study-tour-recommendations', component: StudyTourRecommendations },
    { path: '/description', component: Description },
    { path: '/place-query', component: PlaceQuery },
];

const router = createRouter({
    history: createWebHistory(process.env.BASE_URL),
    routes,
});

export default router;