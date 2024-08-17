import {createRouter, createWebHistory } from 'vue-router'

import HomeView from '../views/HomeView.vue'
import NutritionView from '../views/NutritionView.vue'

const routes = [

  { path: '/',
    name: "home", 
    component: HomeView },

  { path: '/nutrition',
    name: 'nutrition',
    component: NutritionView },
];

const router = createRouter({
  history: createWebHistory(),
  routes,
});

export default router