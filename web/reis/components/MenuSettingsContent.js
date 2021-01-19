app.component('menu-settings', {
    template:
    /*html*/
    `
    <div class="menu-item" v-on:click="callOperation('usuários')">
        <p style="margin: 10px">Usuários</p>
    </div>
    <div class="menu-item" v-on:click="callOperation('reservatório')">
        <p style="margin: 10px">Reservatório</p>
    </div>
    <div class="menu-item" v-on:click="callOperation('tema')">
        <p style="margin: 10px">Tema</p>
    </div>
    <div class="menu-item" v-on:click="callOperation('wallpaper')">
        <p style="margin: 10px">Wallpaper</p>
    </div>
    `,
    methods: {
        callOperation(operation) {

            let window = {
                title: 'Configurar '+ operation + '',
                type: 'settings',
                cat: operation
            }

            this.$emit('open', window)
        }
    }
})