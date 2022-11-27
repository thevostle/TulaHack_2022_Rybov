<template>
	<aside>
		<v-navigation-drawer permanent fixed>
			<template v-slot:prepend>
				<v-list-item lines="two" :prepend-avatar="image" :title="username" subtitle="Logged in"></v-list-item>
			</template>

			<v-divider></v-divider>

			<v-list :lines="false" density="compact" nav>
				<div class="navLinkWrapper">
					<router-link class="navLink" to="/">
						<v-list-item active-color="primary">
							<template v-slot:prepend>
								<v-icon icon="mdi-folder"></v-icon>
							</template>
							Главная
						</v-list-item>
					</router-link>
					<router-link class="navLink" :to="getLinkToProfile">
						<v-list-item active-color="primary">
							<template v-slot:prepend>
								<v-icon icon="mdi-account-multiple"></v-icon>
							</template>
							Мой список
						</v-list-item>
					</router-link>
				</div>
			</v-list>

			<v-divider></v-divider>

			<div class="userGroup">
				<div class="userGroup__user"></div>
			</div>

			<v-list-subheader inset>Группа</v-list-subheader>

			<v-list-item v-for="user in userGroup" :key="user.name" :title="user.name">
				<template v-slot:prepend>
					<v-avatar>
						<v-img :src="image" alt="John"></v-img>
					</v-avatar>
				</template>

				<template v-slot:append>
					<v-btn
						color="grey-lighten-1"
						icon="mdi-close"
						size="x-small"
						variant="text"
						@click="deleteUser(user.name)"
						v-if="user.name !== username"
					></v-btn>
				</template>
			</v-list-item>

			<div class="pa-2">
				<v-btn
					block
					variant="outlined"
					@click="this.showInputNewUser = true"
					v-if="!showInputNewUser && !this.userLimitAchieved"
				>
					Добавить пользователя
				</v-btn>
				<div class="" v-if="showInputNewUser && !userLimitAchieved" v-click-outside="closeInputNewUser">
					<input class="inputNewUser" placeholder="никнейм" v-model="input_newUser" type="text" />
					<v-btn variant="outlined" @click="addUser"> + </v-btn>
				</div>
			</div>

			<div class="pa-2">
				<v-btn block color="secondary" @click="this.showPopup_chooseGenres = true"> Смотреть </v-btn>
			</div>
		</v-navigation-drawer>
		<PopupChooseGenres v-if="showPopup_chooseGenres" name="chooseGenres" @close="this.showPopup_chooseGenres = false" />
	</aside>
</template>

<script>
import image from '../../assets/images/users/pochita_v_tazike.png';
import PopupChooseGenres from '../Popups/PopupChooseGenres.vue';

import api from '../../mixins/api.js';
import cookie from '../../mixins/cookie.js';

export default {
	name: 'HomeAside',
	components: {
		PopupChooseGenres,
	},
	mixins: [api, cookie],
	data() {
		return {
			username: '',
			userId: 0,

			userGroup: [],
			image: image,

			input_newUser: '',
			showInputNewUser: false,

			userLimit: 4,
			userLimitAchieved: false,

			showPopup_chooseGenres: false,
		};
	},
	methods: {
		addUser() {
			if (this.input_newUser !== this.username) {
				this.showInputNewUser = false;
				this.userGroup.push({ name: this.input_newUser });
				this.checkUserLimit();
			}
		},
		deleteUser(usernameToDelete) {
			this.userGroup = this.userGroup.filter(function (obj) {
				return obj.name !== usernameToDelete;
			});

			this.checkUserLimit();
		},
		checkUserLimit() {
			this.userLimitAchieved = false;
			if (this.userGroup.length >= this.userLimit) {
				this.userLimitAchieved = true;
			}
		},
		closeInputNewUser() {
			if (this.showInputNewUser) {
				this.showInputNewUser = false;
				this.input_newUser = '';
			}
		},
		async getUser() {
			const userData = await this.apiPost('user/get/by_id', { id: this.userId });
			this.username = userData.additional.login;
			this.userGroup.push({ name: this.username });
		},
	},
	mounted() {
		this.userId = this.getCookie('id');
		this.getUser()
	},
	computed: {
		getLinkToProfile() {
			return `/user/${this.userId}`;
		},
	},
};
</script>

<style></style>
