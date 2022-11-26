<template>
	<aside>
		<v-navigation-drawer permanent fixed>
			<template v-slot:prepend>
				<v-list-item lines="two" :prepend-avatar="image" :title="username" subtitle="Logged in"></v-list-item>
			</template>

			<v-divider></v-divider>

			<v-list :lines="false" density="compact" nav>
				<div class="navLinkWrapper" v-for="(item, i) in navLinks" :key="i">
					<router-link class="navLink" :to="item.link">
						<v-list-item :value="item" active-color="primary">
							<template v-slot:prepend>
								<v-icon :icon="item.icon"></v-icon>
							</template>
							{{ item.text }}
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
import PopupChooseGenres from '../Popups/PopupChooseGenres.vue'
export default {
	name: 'HomeAside',
	components: {
		PopupChooseGenres
	},
	data() {
		return {
			username: 'thevostle',
			items: [
				{ title: 'Home', icon: 'mdi-home-city' },
				{ title: 'My Account', icon: 'mdi-account' },
				{ title: 'Users', icon: 'mdi-account-group-outline' },
			],
			navLinks: [
				{ text: 'Главная', icon: 'mdi-folder', link: '/' },
				{ text: 'Мой список', icon: 'mdi-account-multiple', link: '/createRoom' },
			],
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
				this.showInputNewUser = false
				this.input_newUser = ''
			}
		},
	},
	mounted() {
		this.userGroup.push({ name: this.username });

		//дебаг
		//this.userGroup.push({name: 'mounted: test1'})
	},
};
</script>

<style></style>
