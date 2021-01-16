app.component('dashboard-display', {
    props: {
        view: {
            type: String,
            required: true
        }
    },
    template:
    /*html*/
    `
    <div class="dashboard">

        <div class="nav-bar">
            <div >
            <transition name='changeview'>
                <div style="margin: 10px" key=1 v-if="view == 'main'"><h4><b>Início</b></h4></div>
                <div style="margin: 10px" key=2 v-else-if="view == 'history'"><h4><b>Histórico</b></h4></div>
            </transition>
            </div>
        </div>
        <transition name='fade'>

            <div key=1 v-if="view == 'main'"><main-display></main-display></div>
            <div key=2 v-else-if="view == 'history'"><history-display></history-display></div>
            </transition>

    </div>
    `
})