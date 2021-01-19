app.component('task-bar-display', {
    props: {
        tasks: {
            type: Array,
            required: true
        }
    },
    template:
    /*html*/
    `
    <div class="task-bar">
        <div v-for="(task, i) in tasks">
            <button type="button" class="btn btn-secondary task-item" v-on:click="changeVisibility(i)">{{ task.title }}</button>
        </div>
    </div>
    `,
    methods: {
        changeVisibility(i) {
            this.tasks[i].setVisible();
            this.tasks.splice(i, 1);
        }
    }
}) 