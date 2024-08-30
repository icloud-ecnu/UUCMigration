# UUCMigratiton: User-Unaware Container Live Migration

As cloud computing and container technologies grow, moving running applications (containers) between servers without stopping them has become essential. However, traditional methods often struggle because they have to repeatedly copy parts of memory that change frequently, which slows everything down.

U2CMigration offers a new way to solve this problem by predicting which parts of memory will change during the move. It uses two clever approaches: one for stable applications and another for those that change a lot. By accurately predicting changes, U2CMigration can reduce the overall moving time and minimize downtime, ensuring a smoother, faster migration process. Tests show that this method cuts the migration time by nearly half compared to current best practices.

# Getting Started
## Dependencies

1. golang >= 1.19
2. protobuf 
3. protobuf-python
4. protobuf-c
5. protobuf-c-devel
6. protobuf-compiler
7. protobuf-devel
8. Python 3.8.8
4. numpy
5. pandas
6. sklearn
9. pytorch 2.0.1

## Installation

```shell

git clone https://github.com/CycleOfStrife/UUCMigration.git
cd criu-3.16.1
make && make install
cd runc 
make && make install
cd Podman
make && make install
```
## Run the UUCMigratiton System


```shell
#linux01
podman run -itd --name mybox docker.io/busybox
podman conatienr checkpoint --live-migration --predict-mode="SSPD" --dirty-file="test.csv" --ip=<linux02IP> --path="/migration" mybox

```

```
#linux02
mkdir /migration
cd /migration
podman container restore -i <the last file> mybox

```

