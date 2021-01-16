app.component('menu-content', {
    template:
    /*html*/
    `
        <div class="menu-item" v-on:click="clickEvent('main')">
            <i style="margin: 10px" class="fa fa-home"></i>
            <p style="margin: 10px">Página inicial</p>
        </div>
        <div class="menu-item">
                <i style="margin: 10px" class="fa fa-water"></i>
            <p style="margin: 10px">Nível atual</p>
        </div>
        <div class="menu-item" v-on:click="clickEvent('history')">
            <i style="margin: 10px" class="fa fa-chart-bar"></i>
            <p style="margin: 10px">Histórico de uso</p>
            <i style="margin: 10px; margin-left: auto; margin-right: 20px" class="fa fa-angle-right"></i>
        </div>
        <div class="menu-item">
            <i style="margin: 10px" class="fa fa-sliders-h"></i>
            <p style="margin: 10px">Configurações</p>
        </div>
        <div class="menu-item">
            <i style="margin: 10px" class="fa fa-sign-out-alt"></i>
            <p style="margin: 10px">Sair</p>
        </div>
   
    `,
    data() {
        return {
        }
    },
    methods: {
        clickEvent(item) {
            this.$emit('menu-click', item)
        }
    }
})