<script setup>
import { RouterLink, RouterView } from 'vue-router';
import 'material-design-icons-iconfont/dist/material-design-icons.css';
</script>

<template>
	<v-app id="inspire" theme="dark">

			<v-navigation-drawer permanent fixed >
				<template v-slot:prepend>
					<v-list-item lines="two" :prepend-avatar="image" :title="username" subtitle="Logged in"></v-list-item>
				</template>

				<v-divider></v-divider>

        <v-list
          :lines="false"
          density="compact"
          nav
        >
        <div 
          class="navLinkWrapper" 
          v-for="(item, i) in navLinks"
          :key="i"
        >
        <router-link 
          class="navLink" 
          :to="item.link"
        >
          <v-list-item
            :value="item"
            active-color="primary"
          >
            <template v-slot:prepend>
              <v-icon :icon="item.icon"></v-icon>
            </template>
            {{item.text}}
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
						<v-btn color="grey-lighten-1" icon="mdi-close" size="x-small" variant="text" @click="deleteUser(user.name)" v-if="user.name !== username"></v-btn>
					</template>
				</v-list-item>

				<div class="pa-2">
					<v-btn block variant="outlined" @click="this.showInputNewUser = true" v-if="!showInputNewUser && !this.userLimitAchieved"> Добавить пользователя </v-btn>
          <div class="" v-if="showInputNewUser && !userLimitAchieved">
            <input class="inputNewUser" placeholder="никнейм" v-model="input_newUser" type="text" />
            <v-btn variant="outlined" @click="addUser"> + </v-btn>
          </div>
				</div>

				<div class="pa-2">
					<v-btn block color="secondary"> Смотреть </v-btn>
				</div>
			</v-navigation-drawer>
			<v-main><RouterView /></v-main>

	</v-app>
</template>

<script>
import image from './assets/images/users/pochita_v_tazike.png';
export default {
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
		};
	},
  methods: {
    addUser() {
      if(this.input_newUser !== this.username) {
        this.showInputNewUser = false
        this.userGroup.push({name: this.input_newUser})
        this.checkUserLimit()
      }
    },
    deleteUser(usernameToDelete) {
      this.userGroup = this.userGroup.filter(
        function ( obj ) {
          return obj.name !== usernameToDelete;
      });

      this.checkUserLimit()
    },
    checkUserLimit() {
      this.userLimitAchieved = false
      if(this.userGroup.length >= this.userLimit) {
        this.userLimitAchieved = true
      }
    }
  },
  mounted() {
    this.userGroup.push({name: this.username})

    //дебаг
    //this.userGroup.push({name: 'mounted: test1'})
  },
};
</script>

<style scoped>

.inputNewUser {
  border: thin solid currentColor;
}








header {
	line-height: 1.5;
	max-height: 100vh;
}

.logo {
	display: block;
	margin: 0 auto 2rem;
}

nav {
	width: 100%;
	font-size: 12px;
	text-align: center;
	margin-top: 2rem;
}

a {
  text-decoration: none;
}

.navLink {
  color: #ebebeba3;
  width: 100%;
}

nav a.router-link-exact-active {
	color: var(--color-text);
}

nav a.router-link-exact-active:hover {
	background-color: transparent;
}

nav a {
	display: inline-block;
	padding: 0 1rem;
	border-left: 1px solid var(--color-border);
}

nav a:first-of-type {
	border: 0;
}

@media (min-width: 1024px) {
	header {
		display: flex;
		place-items: center;
		padding-right: calc(var(--section-gap) / 2);
	}

	.logo {
		margin: 0 2rem 0 0;
	}

	header .wrapper {
		display: flex;
		place-items: flex-start;
		flex-wrap: wrap;
	}

	nav {
		text-align: left;
		margin-left: -1rem;
		font-size: 1rem;

		padding: 1rem 0;
		margin-top: 1rem;
	}
}

.wrapper {
	justify-content: center;
	width: 90%;
	align-self: center;
}
</style>
