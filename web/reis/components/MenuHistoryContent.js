app.component('menu-history', {
    template:
    /*html*/
    `

        <div class="menu-item" v-on:click="callOperation('all')">
            <p style="margin: 10px">Sem filtro</p>
        </div>
        <div class="menu-item" v-on:click="callOperation('dias')">
            <p style="margin: 10px">Filtrar por dia</p>
        </div>
        <div class="menu-item" v-on:click="callOperation('meses')">
            <p style="margin: 10px">Filtrar por mês</p>
        </div>
        <div class="menu-item" v-on:click="callOperation('anos')">
            <p style="margin: 10px">Filtrar por ano</p>
         </div>

    `,
    methods: {
        callOperation(scale) {

            let window = {
                title: 'Histórico de uso ('+ scale + ')',
                type: 'history',
                scale: scale
            }

            this.$emit('open', window)
        }
    }
})