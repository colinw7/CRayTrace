#include <pthread.h>
#include <assert.h>
#include <pthread_rdwr.h>

/* TODO: Writer should get mutex before reader */

int
pthread_rdwr_init_np(pthread_rdwr_t *rdwrp, pthread_rdwrattr_t *attrp)
{
  assert(attrp);

  rdwrp->readers_reading = 0;
  rdwrp->writer_writing  = 0;

  pthread_mutex_init(&rdwrp->mutex, NULL);

  pthread_cond_init(&rdwrp->lock_free, NULL);

  return 0;
}

int
pthread_rdwr_destroy_np(pthread_rdwr_t *rdwrp)
{
  pthread_mutex_destroy(&rdwrp->mutex);

  pthread_cond_destroy(&rdwrp->lock_free);

  return 0;
}

int
pthread_rdwr_rlock_np(pthread_rdwr_t *rdwrp)
{
  pthread_mutex_lock(&rdwrp->mutex);

  while (rdwrp->writer_writing)
    pthread_cond_wait(&rdwrp->lock_free, &rdwrp->mutex);

  ++rdwrp->readers_reading;

  pthread_mutex_unlock(&rdwrp->mutex);

  return 0;
}

int
pthread_rdwr_runlock_np(pthread_rdwr_t *rdwrp)
{
  pthread_mutex_lock(&rdwrp->mutex);

  if (rdwrp->readers_reading == 0) {
    pthread_mutex_unlock(&rdwrp->mutex);
    return -1;
  }
  else {
    --rdwrp->readers_reading;

    if (rdwrp->readers_reading == 0)
      pthread_cond_signal(&rdwrp->lock_free);

    pthread_mutex_unlock(&rdwrp->mutex);

    return 0;
  }
}

int
pthread_rdwr_wlock_np(pthread_rdwr_t *rdwrp)
{
  pthread_mutex_lock(&rdwrp->mutex);

  while (rdwrp->writer_writing || rdwrp->readers_reading)
    pthread_cond_wait(&rdwrp->lock_free, &rdwrp->mutex);

  ++rdwrp->writer_writing;

  pthread_mutex_unlock(&rdwrp->mutex);

  return 0;
}

int
pthread_rdwr_wunlock_np(pthread_rdwr_t *rdwrp)
{
  pthread_mutex_lock(&rdwrp->mutex);

  if (rdwrp->writer_writing == 0) {
    pthread_mutex_unlock(&rdwrp->mutex);
    return -1;
  }
  else {
    rdwrp->writer_writing = 0;

    pthread_cond_broadcast(&rdwrp->lock_free);

    pthread_mutex_unlock(&rdwrp->mutex);

    return 0;
  }
}
