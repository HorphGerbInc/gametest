node('node') {


    currentBuild.result = "SUCCESS"

    try {

       stage('Checkout'){

          checkout scm
       }

       stage('Build') {
           env.NODE_ENV = "build"
           sh 'mkdir build; cd build; cmake ..; make'
       }

       stage('Test'){
         env.NODE_ENV = "test"
       }

       stage('Cleanup'){
       }
    }
    catch (err) {

        currentBuild.result = "FAILURE"
        throw err
    }

}
