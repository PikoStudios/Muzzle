# Plans for implementing Batcher

Instead of an array holding all of the batchers, we can instead have a singular batch.
Whenever we need to seperate batches, for example if we need to try a shape with a seperate shader program, we can simply "flush the batch" by calling end_batch(); begin_batch();

Whenever we run out of room in a batch, instead of creating a new batch in the array, we can instead just just "flush the batch". Because this is all done before the screen clears,
we will still end up with a full frame. This saves on a lot of memory

- Frankie A. May 29th, 2023