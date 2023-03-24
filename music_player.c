#include "queue.h"
#include "dll.h"
#include "music_player.h"
#include <stdio.h>
#include <stdlib.h>

playlist_t* create_playlist() // return a newly created doubly linked list
{
	// DO NOT MODIFY!!!
	playlist_t* playlist = (playlist_t*) malloc(sizeof(playlist_t));
	playlist->list = create_list();
	playlist->num_songs = 0;
	playlist->last_song = NULL;
	return playlist;
}

void delete_playlist(playlist_t* playlist) // delete the playlist
{
	// DO NOT MODIFY!!!
	delete_list(playlist->list);
	free(playlist);
}

music_queue_t* create_music_queue() // return a newly created queue
{
	// DO NOT MODIFY!!!
	return create_queue();
}

void clear_music_queue(music_queue_t* q) // clear the queue q
{	
	// DO NOT MODIFY!!!
	delete_queue(q);
}

void add_song(playlist_t* playlist, int song_id, int where) // TODO: add a song id to the end of the playlist
{
	if(where==-2)
	{
		insert_back(playlist->list,song_id);
		playlist->num_songs++;
	}
	else if(where==-1)
	{
		insert_front(playlist->list,song_id);
		playlist->num_songs++;
	}
	else if(where>=0)
	{
		insert_after(playlist->list,song_id,where);
		playlist->num_songs++;
	}
}

void delete_song(playlist_t* playlist, int song_id) // TODO: remove song id from the playlist
{
	delete_node(playlist->list,song_id);
	playlist->num_songs--;
}

song_t* search_song(playlist_t* playlist, int song_id) // TODO: return a pointer to the node where the song id is present in the playlist
{
	return(search(playlist->list,song_id));
}

void search_and_play(playlist_t* playlist, int song_id) // TODO: play the song with given song_id from the list(no need to bother about the queue. Call to this function should always play the given song and further calls to play_next and play_previous)
{
	song_t* temp=search_song(playlist,song_id);
	if(temp==NULL)
	{
		playlist->last_song=NULL;
		return;
	}
	play_song(temp->data);
	playlist->last_song=temp;
}

void play_next(playlist_t* playlist, music_queue_t* q) // TODO: play the next song in the linked list if the queue is empty. If the queue if not empty, play from the queue
{
	if(empty(q))
	{
		if(playlist->last_song==NULL|| playlist->last_song->next==NULL)
		{
			play_song(playlist->list->head->data);
			playlist->last_song=playlist->list->head;
		}
		else
		{
			play_song(playlist->last_song->next->data);
			playlist->last_song=playlist->last_song->next;
		}
	}
	else
	{
		play_song(dequeue(q));	
	}

	// else if(playlist->last_song==NULL)
	// 	play_song(playlist->list->head->data);
	// else if(playlist->list==NULL)
	// 	return;
	// else
	// {
	// 	play_song(q->front);
	// 	playlist->last_song=playlist->last_song->next;
	// }

}

void play_previous(playlist_t* playlist) // TODO: play the previous song from the linked list
{
	if(playlist->num_songs==0)
		return;
	if(playlist->last_song==NULL || playlist->last_song->prev==NULL)
	{
		play_song(playlist->list->tail->data);
		playlist->last_song=playlist->list->tail;
		return;
	}
			play_song(playlist->last_song->prev->data);
			playlist->last_song=playlist->last_song->prev;

}

void play_from_queue(music_queue_t* q) // TODO: play a song from the queue
{
	play_song(q->front->data);
	// playlist->last_song=q->front;
}

void insert_to_queue(music_queue_t* q, int song_id) // TODO: insert a song id to the queue
{
	enqueue(q,song_id);
}

void reverse(playlist_t* playlist) // TODO: reverse the order of the songs in the given playlist. (Swap the nodes, not data)
{
	song_t *temp;
	song_t *curr=NULL;
	song_t *first=playlist->list->head;
	while(first!=NULL)
	{
		temp=first->next;
		first->prev=temp;
		first->next=curr;
		curr=first;
		first=temp;
	}
	playlist->list->tail=playlist->list->head;
	playlist->list->head=curr;
}

void k_swap(playlist_t* playlist, int k) // TODO: swap the node at position i with node at position i+k upto the point where i+k is less than the size of the linked list
{
	int n=playlist->num_songs;
	int i=0;
	song_t *temp = playlist->list->head;
	song_t *curr = playlist->list->head;
	for (i = 0; i + k < n; i++)
	{
		curr = temp;
		for (int y = 0; y < k; y++)
		{
			curr = curr->next;
		}
		song_t *currnext = curr->next;
		song_t *currprev = curr->prev;
		song_t *temp1 = temp->next;
		song_t *temp2 = temp->prev;
		if (k == 1)
		{
			currprev = curr;
			temp1 = temp;
		}
		curr->next = temp1;
		curr->prev = temp2;
		temp->next = currnext;
		temp->prev = currprev;
		if (temp1 != NULL)
			temp1->prev = curr;
		if (currnext != NULL)
			currnext->prev = temp;
		if (currprev != NULL)
			currprev->next = temp;

		if (temp == playlist->list->head)
		{
			playlist->list->head = curr;
		}
		else
		{
			temp2->next = curr;
		}
		temp = temp1;
	}

	song_t *last = playlist->list->head;
	song_t *slast = NULL;
	while (last != NULL)
	{
		slast = last;
		last = last->next;
	}
	playlist->list->tail = slast;
}

void shuffle(playlist_t* playlist, int k) // TODO: perform k_swap and reverse
{
	k_swap(playlist,k);
	reverse(playlist);
		
}

song_t* debug(playlist_t* playlist) // TODO: if the given linked list has a cycle, return the start of the cycle, else return null. Check cycles only in forward direction i.e with the next pointer. No need to check for cycles in the backward pointer.
{
	song_t *i=playlist->list->head;
	for(song_t *i=playlist->list->head;i->next!=NULL;i=i->next)
	{
		if(i->next->prev!=i)
			return(i->next);
	}
	return(NULL);
}

void display_playlist(playlist_t* p) // Displays the playlist
{
	// DO NOT MODIFY!!!
	display_list(p->list);
}

void play_song(int song_id)
{
	// DO NOT MODIFY!!!
	printf("Playing: %d\n", song_id);
}

