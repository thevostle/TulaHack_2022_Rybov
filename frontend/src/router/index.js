import { createRouter, createWebHistory } from 'vue-router'
import Home from '../views/Home.vue'

const router = createRouter({
	mode: 'history',
	history: createWebHistory(import.meta.env.BASE_URL),
	routes: [
		{
			path: '/',
			name: 'Home',
			component: Home,
		},
		{
			path: '/auth/',
			name: 'Auth',
			component: () => import('../views/Auth.vue'),
		},
		{
			path: '/user/:userId(\\d+)',
			name: 'User profile',
			component: () => import('../views/UserProfile.vue'),
		},
		{
			path: '/room/:roomId(\\d+)',
			name: 'Room',
			component: () => import('../views/Room.vue'),
		},
		{
			path: '/createRoom',
			name: 'Room creation',
			component: () => import('../views/NewRoom.vue'),
		},
	],
});

export default router
